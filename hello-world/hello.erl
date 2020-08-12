% erl -noshell -eval "hello:hello()" -eval 'init:stop()'

-module(hello).
-compile(export_all).

hello() ->
    io:format("hello world~n").