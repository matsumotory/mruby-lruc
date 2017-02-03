# mruby-lruc   [![Build Status](https://travis-ci.org/matsumotory/mruby-lruc.svg?branch=master)](https://travis-ci.org/matsumotory/mruby-lruc)
LRUC class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'matsumotory/mruby-lruc'
end
```
## example
```ruby
p LRUC.hi
#=> "hi!!"
t = LRUC.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
