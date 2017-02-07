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

assert("LRUC#total_memory") do
  l = LRUC.new 1024, 1024
  assert_equal(1024, l.total_memory)
end

assert("LRUC#free_memory") do
  l = LRUC.new 1024, 1024
  assert_equal(1024, l.free_memory)
end

assert("LRUC#average_item_length") do
  l = LRUC.new 1024, 1024
  assert_equal(1024, l.average_item_length)
end

assert("LRUC#access_count") do
  l = LRUC.new 1024, 1024
  10000.times do
    l.set "hoge", "fuga"
    assert_equal("fuga", l.get("hoge"))
  end
  assert_equal(20000, l.access_count)
end

assert('LRUC#{new,free}') do
  10000.times do
    l = LRUC.new 1024, 1024
    l.set "hoge", "fuga"
    assert_nil(l.free)
  end
end
