require 'mkmf'
dir_config("hello_cairo")
$CFLAGS = `pkg-config --cflags cairo`
$LDFLAGS = `pkg-config --libs cairo`
create_makefile("hello_cairo")
