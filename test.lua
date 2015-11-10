function aaa()
	local i = i or 0
	while i < 10 do
		i = i + 1
		print(i)
		coroutine.yield()
	end
end

function Func1(param1)
	Func2(param1 + 10)
	print("Func1 ended." )
	return 30
end

function Func2(value)
	coroutine.yield (10, value)
	print("Func2 ended." )
end

function add(x,y)
       return x + y
end 

function bbb()
	while 1 do
		x = zsleep(3) --调度c里面的zsleep寒素
		print(x)
	end
end

bbb()
