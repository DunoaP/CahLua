
print("Instance foo:")
print("foo.teststring		= " .. foo.string)
print("foo.testnumber		= " .. foo.number)
--print("foo.testboolean		= " .. foo.boolean)

foo.string = "We changed the member!"
foo.number = 1337
--foo.boolean = false

print("Instance foo after changes:")
print("foo.teststring		= " .. foo.string)
--print("foo.testboolean		= " .. foo.boolean)
print("foo.testnumber		= " .. foo.number)
