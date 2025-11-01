/* Memory layout for ESP32-C3 */
/* ESP32-C3 has 400KB of SRAM and 4MB of Flash */

MEMORY
{
  /* Instruction RAM */
  IRAM : ORIGIN = 0x4037C000, LENGTH = 400K
  
  /* Data RAM */
  DRAM : ORIGIN = 0x3FC80000, LENGTH = 400K
  
  /* External Flash - for code */
  /* Note: Actual usable flash depends on partition table */
  FLASH : ORIGIN = 0x42000000, LENGTH = 4M
  
  /* RTC fast memory (not used by default) */
  RTC_FAST : ORIGIN = 0x50000000, LENGTH = 8K
}

/* Entry point */
ENTRY(ESP32Reset)

SECTIONS {
  .text : {
    *(.text .text.*)
  } > FLASH
  
  .rodata : {
    *(.rodata .rodata.*)
  } > FLASH
  
  .data : {
    *(.data .data.*)
  } > DRAM AT > FLASH
  
  .bss : {
    *(.bss .bss.*)
  } > DRAM
}
