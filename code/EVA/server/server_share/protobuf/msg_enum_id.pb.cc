// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_enum_id.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "msg_enum_id.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace PROTOBUF {

namespace {

const ::google::protobuf::EnumDescriptor* PB_TErrorEnum_descriptor_ = NULL;
const ::google::protobuf::EnumDescriptor* PB_DotItem_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_msg_5fenum_5fid_2eproto() {
  protobuf_AddDesc_msg_5fenum_5fid_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "msg_enum_id.proto");
  GOOGLE_CHECK(file != NULL);
  PB_TErrorEnum_descriptor_ = file->enum_type(0);
  PB_DotItem_descriptor_ = file->enum_type(1);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_msg_5fenum_5fid_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_msg_5fenum_5fid_2eproto() {
}

void protobuf_AddDesc_msg_5fenum_5fid_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\021msg_enum_id.proto\022\010PROTOBUF*&\n\rPB_TErr"
    "orEnum\022\025\n\021ERROR_SERVER_FULL\020\000*p\n\nPB_DotI"
    "tem\022\027\n\023DOT_ADD_CREATE_ROLE\020\001\022\032\n\026DOT_ADD_"
    "PROXY_RECHARGE\020\002\022\024\n\020DOT_ADD_SHOP_BUY\020\003\022\027"
    "\n\023DOT_SUB_CREATE_ROOM\0202", 183);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "msg_enum_id.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_msg_5fenum_5fid_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_msg_5fenum_5fid_2eproto {
  StaticDescriptorInitializer_msg_5fenum_5fid_2eproto() {
    protobuf_AddDesc_msg_5fenum_5fid_2eproto();
  }
} static_descriptor_initializer_msg_5fenum_5fid_2eproto_;
const ::google::protobuf::EnumDescriptor* PB_TErrorEnum_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PB_TErrorEnum_descriptor_;
}
bool PB_TErrorEnum_IsValid(int value) {
  switch(value) {
    case 0:
      return true;
    default:
      return false;
  }
}

const ::google::protobuf::EnumDescriptor* PB_DotItem_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PB_DotItem_descriptor_;
}
bool PB_DotItem_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 50:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PROTOBUF

// @@protoc_insertion_point(global_scope)
