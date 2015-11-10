#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "assert.h"

int
luaadd(lua_State* L, int x, int y)
{
        int sum;
/*the function name*/
        lua_getglobal(L,"add");
/*the first argument*/
        lua_pushnumber(L, x);
/*the second argument*/
        lua_pushnumber(L, y);
/*call the function with 2 arguments, return 1 result.*/
        lua_call(L, 2, 1);
/*get the result.*/
        sum = (int)lua_tonumber(L, -1);
/*cleanup the return*/
        lua_pop(L,1);
        return sum;
}

int zsleep( lua_State *L )
{
	int sec = (int)lua_tonumber( L, -1 );
	return lua_yield( L, 0 );
}

int do_script( lua_State *L, const char *script )
{
	lua_pushcfunction( L, zsleep );
	lua_setglobal( L, "zsleep" );

	int error = luaL_loadfile( L, script ); //luaL_dofile区别很大,dofile 直接运行且调度yield会出问题
	if( error != 0 )
	{
		printf(  "load script [%s] failed\n", script );
		return -1;
	}

	printf("begin\n");
	lua_resume( L, 0 ); //loadfile 只加载未运行，这句话就开始运行了，相当于执行脚本里的bbb()0,调度到yield回返回出来
	printf("do script end\n");
	return 0;
}

int main(int argc, char *argv[])
{
#if 0
	L = lua_open();
	luaopen_base(L);
	const char *buf = "function main(number) number = number + 1 return number end";
	luaL_dostring(L,buf);
	lua_getglobal(L, "main");
	lua_pushnumber(L, 100);
	lua_pcall(L, 1, 1, 0);
	int result = lua_tonumber(L, -1);
	printf("result = %d\n", result);
	assert(result == 101);
	lua_close(L);
#else
	int sum;
	/*initialize Lua*/
	lua_State* L = lua_open();
	/*load Lua base libraries*/
	luaL_openlibs(L);
	luaopen_base(L);

	/*load the script*/
	do_script( L, "test.lua" );
	/*call the add function*/
	sum = luaadd(L, 10, 15); //调度脚本里面的add函数
	/*print the result*/
	printf("The sum is %d \n",sum);
	
	while(1) {
		sleep(1);
		lua_resume( L, 0 );	
	}
	
	/*cleanup Lua*/
	lua_close(L);
	
#endif
	return 0;
}

