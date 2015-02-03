function Start()
	print("Instance foo:")
	--[[foo.string = "Script number 1!"
	print("foo.teststring		= " .. foo.string)
	print("foo.testnumber		= " .. foo.number)
	
	foo.string = "Script number 1!"
	foo.number = 1

	print("Instance foo after changes:")
	print("foo.teststring		= " .. foo.string)
	print("foo.testnumber		= " .. foo.number)
	]]--
end