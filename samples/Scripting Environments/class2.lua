function Start()
	print("Script 2:")
	
	foo.string = "Hello World2"
	print("foo.teststring               = " .. foo.string)
	foo.string = "Script number 2!"
	print("foo.teststring changed to    = " .. foo.string)
	
	foo.number = 0
	print("foo.testnumber               = " .. foo.number)
	foo.number = -80
	print("foo.testnumber changed to    = " .. foo.number)
end