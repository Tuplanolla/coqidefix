# CoqIDEFix

This hack makes it possible to
use a custom color theme with a dark background in CoqIDE.

## Usage

Put the values of `background_color`, `processed_color` and `processing_color`
from `~/.config/coq/coqiderc` into `coqidefix.h` or vice versa,
edit `change` in `coqidefix.c` for more precise control,
compile `coqidefix.so` by calling `make`,
copy `coqide-gtk2rc` into `~/.config/coq/coqide-gtk2rc` and
call `coqide` with `LD_PRELOAD=./coqidefix.so coqide`.

## Alternative

Edit `ide/tags.ml` and recompile CoqIDE.

## History

This trick was written by Sampsa "Tuplanolla" Kiiskinen on 2015-08-03.

## Picture

![Screenshot](http://raw.github.com/Tuplanolla/coqidefix/master/coqidefix.png)
