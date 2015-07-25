

chip = 18f4550

all: kades.hex

%.p1 %.pre %.d: %.c
	xc8 --chip=${chip} --pass1 $<

kades.hex: kades.p1 desuicide.p1 gamedb.p1 games.p1 hardware.p1 lcd.p1 timer.p1 ui.p1
	xc8 --chip=${chip} --output=intel $^

clean:
	rm \*.d \*.pre \*.p1 \*.sdb \*.as \*.obj \*.sym \*.cmf startup.lst startup.rlf -f

clobber: clean
	rm \*.cof \*.hex -f