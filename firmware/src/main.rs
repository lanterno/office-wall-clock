//! Wall Clock In Machine - Rust Firmware for ESP32-C6 DevKitC-1
//!
//! Uses state-of-the-art Rust embedded tools:
//! - esp-hal: Pure Rust hardware abstraction
//! - Embassy: Modern async/await runtime
//! - defmt: Zero-cost logging

#![no_std]
#![no_main]

extern crate alloc;

use esp_backtrace as _;
use esp_hal::{
    clock::ClockControl,
    embassy,
    gpio::{Input, Output, PullUp, PushPull, IO},
    peripherals::Peripherals,
    prelude::*,
    rmt::Rmt,
    system::SystemControl,
    timer::timg::TimerGroup,
};
use embassy_executor::Spawner;
use embassy_time::{Duration, Timer};
use defmt::*;

mod config;
mod tasks;

use tasks::{button::button_task, led::led_task, wifi::wifi_task};

#[global_allocator]
static ALLOCATOR: esp_alloc::EspHeap = esp_alloc::EspHeap::empty();

fn init_heap() {
    const HEAP_SIZE: usize = 32 * 1024;
    static mut HEAP: core::mem::MaybeUninit<[u8; HEAP_SIZE]> = core::mem::MaybeUninit::uninit();
    unsafe {
        ALLOCATOR.init(HEAP.as_mut_ptr() as *mut u8, HEAP_SIZE);
    }
}

#[main]
async fn main(spawner: Spawner) {
    init_heap();
    
    info!("=================================");
    info!("Wall Clock In Machine (Rust)");
    info!("Version: {}", env!("CARGO_PKG_VERSION"));
    info!("Target: ESP32-C6 (RISC-V)");
    info!("Runtime: Embassy async");
    info!("=================================");

    let peripherals = Peripherals::take();
    let system = SystemControl::new(peripherals.SYSTEM);
    let clocks = ClockControl::max(system.clock_control).freeze();
    let timer_group0 = TimerGroup::new(peripherals.TIMG0, &clocks);
    embassy::init(&clocks, timer_group0);

    let io = IO::new(peripherals.GPIO, peripherals.IO_MUX);
    
    info!("Initializing peripherals...");

    let button_pin = Input::new(io.pins.gpio9, PullUp);
    let led_pin = io.pins.gpio8;
    let rmt = Rmt::new(peripherals.RMT, 80.MHz(), &clocks).unwrap();
    
    info!("Spawning async tasks...");
    
    spawner.spawn(button_task(button_pin)).ok();
    spawner.spawn(led_task(led_pin, rmt.channel0)).ok();
    spawner.spawn(wifi_task(peripherals.WIFI, &clocks, timer_group0)).ok();
    
    info!("All tasks spawned. Entering main loop...");
    
    loop {
        Timer::after(Duration::from_secs(10)).await;
        debug!("Heartbeat: System running");
    }
}

#[panic_handler]
fn panic(info: &core::panic::PanicInfo) -> ! {
    error!("PANIC: {}", defmt::Display2Format(info));
    loop {}
}
}
