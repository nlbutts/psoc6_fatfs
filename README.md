# psoc6_fatfs
An implementation of FatFs for the PSoC 6. This project uses R0.13c version of the [FatFs library](http://elm-chan.org/fsw/ff/00index_e.html). 

This is meant to be very simple, support reads/writes to/from an SD card. 
The [CY8CPROTO-062-4343W](https://www.cypress.com/documentation/development-kitsboards/psoc-6-wi-fi-bt-prototyping-kit-cy8cproto-062-4343w) board was used for development. Directory listing and reads are working. I can get the Cypress
PDL library to write data to the SD card. If anyone has ideas, please let me know.
