function Start()
	print("Script 1:")
		
	foo.string = "Hello World"
	print("foo.teststring               = " .. foo.string)
	foo.string = "Script number 1!"
	print("foo.teststring changed to    = " .. foo.string)
	
	foo.number = 1
	print("foo.testnumber               = " .. foo.number)
	foo.number = 2
	print("foo.testnumber changed to    = " .. foo.number)
end