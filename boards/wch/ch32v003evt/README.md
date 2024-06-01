### Setup

Install https://github.com/cnlohr/ch32v003fun/tree/master/minichlink

### Usage

```
west update

west build -p always -b wch_ch32v003evt samples/basic/blinky

west flash
```

### Tips

- To unbrick the chip, simple execute the `minichlink -u` command.

### Tested On

- Bare CH32V003J4M6 SOP-8 chip

- WCH CH32V003EVT board (CH32V003 Evaluation Kit)
