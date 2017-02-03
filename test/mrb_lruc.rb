##
## LRUC Test
##

assert("LRUC#set/get") do
  l = LRUC.new 1024, 1024
  l.set "hoge", "fuga"
  assert_equal("fuga", l.get("hoge"))
end

assert("LRUC#[]=/[]") do
  l = LRUC.new 1024, 1024
  l["hoge"] = "fuga"
  assert_equal("fuga", l["hoge"])
end

assert("LRUC#delete") do
  l = LRUC.new 1024, 1024
  l.set "hoge", "fuga"
  assert_equal("fuga", l.get("hoge"))
  l.delete "hoge"
  assert_nil(l.get("hoge"))
end

assert("LRUC#set") do
  l = LRUC.new 1024, 1024
  10000.times do
    l.set "hoge", "fuga"
    assert_equal("fuga", l.get("hoge"))
  end
end

