set PROTO_OUT=../../server/server_share/Protobuf

protoc.exe --cpp_out=%PROTO_OUT% ./msg_login.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_error_id.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_player.proto

pause
