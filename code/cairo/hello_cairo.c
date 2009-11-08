#include <cairo.h>
#include <ruby.h>

VALUE Cairo = Qnil;
VALUE Surface = Qnil;
VALUE method_surface_initialize(VALUE self, VALUE width, VALUE height);
VALUE method_surface_set_color(VALUE self, VALUE red, VALUE green, VALUE blue);
VALUE method_surface_move_to(VALUE self, VALUE x, VALUE y);
VALUE method_surface_show_text(VALUE self, VALUE text);
VALUE method_surface_save(VALUE self, VALUE fname);
VALUE method_surface_cleanup(VALUE self);
cairo_surface_t *surface;
cairo_t *cr;
void Init_hello_cairo() {
  Cairo = rb_define_module("Cairo");
  Surface = rb_define_class_under(Cairo,"Surface",rb_cObject);
  rb_define_method(Surface,"initialize",method_surface_initialize,2);
  rb_define_method(Surface,"set_color",method_surface_set_color,3);
  rb_define_method(Surface,"show_text",method_surface_show_text,1);
  rb_define_method(Surface,"move_to",method_surface_move_to,2);
  rb_define_method(Surface,"save",method_surface_save,1);
  rb_define_method(Surface,"cleanup",method_surface_cleanup,0);
}

VALUE method_surface_initialize(VALUE self, VALUE width, VALUE height){
  surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, NUM2INT(width), NUM2INT(height));
  cr = cairo_create(surface);
  return Qnil;
}

VALUE method_surface_set_color(VALUE self, VALUE red, VALUE green, VALUE blue) {
  cairo_set_source_rgb (cr, NUM2DBL(red), NUM2DBL(green), NUM2DBL(blue));
  return Qnil;
}
VALUE method_surface_move_to(VALUE self, VALUE x, VALUE y){
  cairo_move_to(cr, NUM2DBL(x), NUM2DBL(y));
  return Qnil;
}

VALUE method_surface_show_text(VALUE self, VALUE text){
  cairo_select_font_face (cr, "serif", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_BOLD);
  cairo_set_font_size (cr, 32.0);
  cairo_show_text(cr, StringValueCStr(text));
  return text;
}

VALUE method_surface_save(VALUE self, VALUE fname){
  cairo_surface_write_to_png(surface, StringValueCStr(fname));
  return fname;
}

VALUE method_surface_cleanup(VALUE self){
  cairo_destroy(cr);
  cairo_surface_destroy(surface);
  return Qnil;
}
