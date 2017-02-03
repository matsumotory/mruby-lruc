# mruby-lruc   [![Build Status](https://travis-ci.org/matsumotory/mruby-lruc.svg?branch=master)](https://travis-ci.org/matsumotory/mruby-lruc)

Least Recently Used(LRU) cache using [lruc](https://github.com/willcannings/C-LRU-Cache)

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
assert("LRUC#set/get") do
  l = LRUC.new 1024, 1024
  l.set "hoge", "fuga"
  assert_equal("fuga", l.get("hoge"))
end
```

## License
under the MIT License:
- see LICENSE file
