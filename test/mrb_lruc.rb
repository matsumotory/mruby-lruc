##
## LRUC Test
##

assert("LRUC#set/get") do
  l = LRUC.new 1024, 1024
  l.set "hoge", "fuga"
  assert_equal("fuga", l.get("hoge"))
end

assert("LRUC#set/get") do
  l = LRUC.new 1024, 1024
  l.set "hoge", "fuga"
  assert_equal("fuga", l.get("hoge"))
end
