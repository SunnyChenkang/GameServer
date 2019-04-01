set PROTO_OUT=../../server/server_share/Protobuf

protoc.exe --cpp_out=%PROTO_OUT% ./msg_login.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_enum_id.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_player.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_room.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_item.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_statistics.proto
protoc.exe --cpp_out=%PROTO_OUT% ./msg_mission.proto

pause
