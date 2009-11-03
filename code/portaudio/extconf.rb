# Loads mkmf which is used to make makefiles for Ruby extensions
require 'mkmf'

dir_config('tweet')
create_makefile('tweet')
