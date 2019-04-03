// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_login.proto

#ifndef PROTOBUF_msg_5flogin_2eproto__INCLUDED
#define PROTOBUF_msg_5flogin_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace PROTOBUF {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_msg_5flogin_2eproto();
void protobuf_AssignDesc_msg_5flogin_2eproto();
void protobuf_ShutdownFile_msg_5flogin_2eproto();

class PB_LoginAuthUser;
class PB_UserLogin;

// ===================================================================

class PB_LoginAuthUser : public ::google::protobuf::Message {
 public:
  PB_LoginAuthUser();
  virtual ~PB_LoginAuthUser();

  PB_LoginAuthUser(const PB_LoginAuthUser& from);

  inline PB_LoginAuthUser& operator=(const PB_LoginAuthUser& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PB_LoginAuthUser& default_instance();

  void Swap(PB_LoginAuthUser* other);

  // implements Message ----------------------------------------------

  PB_LoginAuthUser* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PB_LoginAuthUser& from);
  void MergeFrom(const PB_LoginAuthUser& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 role_id = 1;
  inline bool has_role_id() const;
  inline void clear_role_id();
  static const int kRoleIdFieldNumber = 1;
  inline ::google::protobuf::uint32 role_id() const;
  inline void set_role_id(::google::protobuf::uint32 value);

  // optional uint32 role_kind = 2;
  inline bool has_role_kind() const;
  inline void clear_role_kind();
  static const int kRoleKindFieldNumber = 2;
  inline ::google::protobuf::uint32 role_kind() const;
  inline void set_role_kind(::google::protobuf::uint32 value);

  // optional string client_host = 3;
  inline bool has_client_host() const;
  inline void clear_client_host();
  static const int kClientHostFieldNumber = 3;
  inline const ::std::string& client_host() const;
  inline void set_client_host(const ::std::string& value);
  inline void set_client_host(const char* value);
  inline void set_client_host(const char* value, size_t size);
  inline ::std::string* mutable_client_host();
  inline ::std::string* release_client_host();
  inline void set_allocated_client_host(::std::string* client_host);

  // optional string client_token = 4;
  inline bool has_client_token() const;
  inline void clear_client_token();
  static const int kClientTokenFieldNumber = 4;
  inline const ::std::string& client_token() const;
  inline void set_client_token(const ::std::string& value);
  inline void set_client_token(const char* value);
  inline void set_client_token(const char* value, size_t size);
  inline ::std::string* mutable_client_token();
  inline ::std::string* release_client_token();
  inline void set_allocated_client_token(::std::string* client_token);

  // @@protoc_insertion_point(class_scope:PROTOBUF.PB_LoginAuthUser)
 private:
  inline void set_has_role_id();
  inline void clear_has_role_id();
  inline void set_has_role_kind();
  inline void clear_has_role_kind();
  inline void set_has_client_host();
  inline void clear_has_client_host();
  inline void set_has_client_token();
  inline void clear_has_client_token();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 role_id_;
  ::google::protobuf::uint32 role_kind_;
  ::std::string* client_host_;
  ::std::string* client_token_;
  friend void  protobuf_AddDesc_msg_5flogin_2eproto();
  friend void protobuf_AssignDesc_msg_5flogin_2eproto();
  friend void protobuf_ShutdownFile_msg_5flogin_2eproto();

  void InitAsDefaultInstance();
  static PB_LoginAuthUser* default_instance_;
};
// -------------------------------------------------------------------

class PB_UserLogin : public ::google::protobuf::Message {
 public:
  PB_UserLogin();
  virtual ~PB_UserLogin();

  PB_UserLogin(const PB_UserLogin& from);

  inline PB_UserLogin& operator=(const PB_UserLogin& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const PB_UserLogin& default_instance();

  void Swap(PB_UserLogin* other);

  // implements Message ----------------------------------------------

  PB_UserLogin* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PB_UserLogin& from);
  void MergeFrom(const PB_UserLogin& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional uint32 role_id = 1;
  inline bool has_role_id() const;
  inline void clear_role_id();
  static const int kRoleIdFieldNumber = 1;
  inline ::google::protobuf::uint32 role_id() const;
  inline void set_role_id(::google::protobuf::uint32 value);

  // optional uint32 role_kind = 2;
  inline bool has_role_kind() const;
  inline void clear_role_kind();
  static const int kRoleKindFieldNumber = 2;
  inline ::google::protobuf::uint32 role_kind() const;
  inline void set_role_kind(::google::protobuf::uint32 value);

  // optional uint32 frontend_service_id = 3;
  inline bool has_frontend_service_id() const;
  inline void clear_frontend_service_id();
  static const int kFrontendServiceIdFieldNumber = 3;
  inline ::google::protobuf::uint32 frontend_service_id() const;
  inline void set_frontend_service_id(::google::protobuf::uint32 value);

  // optional uint32 game_service_id = 4;
  inline bool has_game_service_id() const;
  inline void clear_game_service_id();
  static const int kGameServiceIdFieldNumber = 4;
  inline ::google::protobuf::uint32 game_service_id() const;
  inline void set_game_service_id(::google::protobuf::uint32 value);

  // optional string client_host = 5;
  inline bool has_client_host() const;
  inline void clear_client_host();
  static const int kClientHostFieldNumber = 5;
  inline const ::std::string& client_host() const;
  inline void set_client_host(const ::std::string& value);
  inline void set_client_host(const char* value);
  inline void set_client_host(const char* value, size_t size);
  inline ::std::string* mutable_client_host();
  inline ::std::string* release_client_host();
  inline void set_allocated_client_host(::std::string* client_host);

  // @@protoc_insertion_point(class_scope:PROTOBUF.PB_UserLogin)
 private:
  inline void set_has_role_id();
  inline void clear_has_role_id();
  inline void set_has_role_kind();
  inline void clear_has_role_kind();
  inline void set_has_frontend_service_id();
  inline void clear_has_frontend_service_id();
  inline void set_has_game_service_id();
  inline void clear_has_game_service_id();
  inline void set_has_client_host();
  inline void clear_has_client_host();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 role_id_;
  ::google::protobuf::uint32 role_kind_;
  ::google::protobuf::uint32 frontend_service_id_;
  ::google::protobuf::uint32 game_service_id_;
  ::std::string* client_host_;
  friend void  protobuf_AddDesc_msg_5flogin_2eproto();
  friend void protobuf_AssignDesc_msg_5flogin_2eproto();
  friend void protobuf_ShutdownFile_msg_5flogin_2eproto();

  void InitAsDefaultInstance();
  static PB_UserLogin* default_instance_;
};
// ===================================================================


// ===================================================================

// PB_LoginAuthUser

// optional uint32 role_id = 1;
inline bool PB_LoginAuthUser::has_role_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PB_LoginAuthUser::set_has_role_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PB_LoginAuthUser::clear_has_role_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PB_LoginAuthUser::clear_role_id() {
  role_id_ = 0u;
  clear_has_role_id();
}
inline ::google::protobuf::uint32 PB_LoginAuthUser::role_id() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_LoginAuthUser.role_id)
  return role_id_;
}
inline void PB_LoginAuthUser::set_role_id(::google::protobuf::uint32 value) {
  set_has_role_id();
  role_id_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_LoginAuthUser.role_id)
}

// optional uint32 role_kind = 2;
inline bool PB_LoginAuthUser::has_role_kind() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PB_LoginAuthUser::set_has_role_kind() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PB_LoginAuthUser::clear_has_role_kind() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PB_LoginAuthUser::clear_role_kind() {
  role_kind_ = 0u;
  clear_has_role_kind();
}
inline ::google::protobuf::uint32 PB_LoginAuthUser::role_kind() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_LoginAuthUser.role_kind)
  return role_kind_;
}
inline void PB_LoginAuthUser::set_role_kind(::google::protobuf::uint32 value) {
  set_has_role_kind();
  role_kind_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_LoginAuthUser.role_kind)
}

// optional string client_host = 3;
inline bool PB_LoginAuthUser::has_client_host() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PB_LoginAuthUser::set_has_client_host() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PB_LoginAuthUser::clear_has_client_host() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PB_LoginAuthUser::clear_client_host() {
  if (client_host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_->clear();
  }
  clear_has_client_host();
}
inline const ::std::string& PB_LoginAuthUser::client_host() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_LoginAuthUser.client_host)
  return *client_host_;
}
inline void PB_LoginAuthUser::set_client_host(const ::std::string& value) {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  client_host_->assign(value);
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_LoginAuthUser.client_host)
}
inline void PB_LoginAuthUser::set_client_host(const char* value) {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  client_host_->assign(value);
  // @@protoc_insertion_point(field_set_char:PROTOBUF.PB_LoginAuthUser.client_host)
}
inline void PB_LoginAuthUser::set_client_host(const char* value, size_t size) {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  client_host_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PROTOBUF.PB_LoginAuthUser.client_host)
}
inline ::std::string* PB_LoginAuthUser::mutable_client_host() {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:PROTOBUF.PB_LoginAuthUser.client_host)
  return client_host_;
}
inline ::std::string* PB_LoginAuthUser::release_client_host() {
  clear_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = client_host_;
    client_host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void PB_LoginAuthUser::set_allocated_client_host(::std::string* client_host) {
  if (client_host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete client_host_;
  }
  if (client_host) {
    set_has_client_host();
    client_host_ = client_host;
  } else {
    clear_has_client_host();
    client_host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:PROTOBUF.PB_LoginAuthUser.client_host)
}

// optional string client_token = 4;
inline bool PB_LoginAuthUser::has_client_token() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PB_LoginAuthUser::set_has_client_token() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PB_LoginAuthUser::clear_has_client_token() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PB_LoginAuthUser::clear_client_token() {
  if (client_token_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_token_->clear();
  }
  clear_has_client_token();
}
inline const ::std::string& PB_LoginAuthUser::client_token() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_LoginAuthUser.client_token)
  return *client_token_;
}
inline void PB_LoginAuthUser::set_client_token(const ::std::string& value) {
  set_has_client_token();
  if (client_token_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_token_ = new ::std::string;
  }
  client_token_->assign(value);
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_LoginAuthUser.client_token)
}
inline void PB_LoginAuthUser::set_client_token(const char* value) {
  set_has_client_token();
  if (client_token_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_token_ = new ::std::string;
  }
  client_token_->assign(value);
  // @@protoc_insertion_point(field_set_char:PROTOBUF.PB_LoginAuthUser.client_token)
}
inline void PB_LoginAuthUser::set_client_token(const char* value, size_t size) {
  set_has_client_token();
  if (client_token_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_token_ = new ::std::string;
  }
  client_token_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PROTOBUF.PB_LoginAuthUser.client_token)
}
inline ::std::string* PB_LoginAuthUser::mutable_client_token() {
  set_has_client_token();
  if (client_token_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_token_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:PROTOBUF.PB_LoginAuthUser.client_token)
  return client_token_;
}
inline ::std::string* PB_LoginAuthUser::release_client_token() {
  clear_has_client_token();
  if (client_token_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = client_token_;
    client_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void PB_LoginAuthUser::set_allocated_client_token(::std::string* client_token) {
  if (client_token_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete client_token_;
  }
  if (client_token) {
    set_has_client_token();
    client_token_ = client_token;
  } else {
    clear_has_client_token();
    client_token_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:PROTOBUF.PB_LoginAuthUser.client_token)
}

// -------------------------------------------------------------------

// PB_UserLogin

// optional uint32 role_id = 1;
inline bool PB_UserLogin::has_role_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PB_UserLogin::set_has_role_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PB_UserLogin::clear_has_role_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PB_UserLogin::clear_role_id() {
  role_id_ = 0u;
  clear_has_role_id();
}
inline ::google::protobuf::uint32 PB_UserLogin::role_id() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_UserLogin.role_id)
  return role_id_;
}
inline void PB_UserLogin::set_role_id(::google::protobuf::uint32 value) {
  set_has_role_id();
  role_id_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_UserLogin.role_id)
}

// optional uint32 role_kind = 2;
inline bool PB_UserLogin::has_role_kind() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PB_UserLogin::set_has_role_kind() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PB_UserLogin::clear_has_role_kind() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PB_UserLogin::clear_role_kind() {
  role_kind_ = 0u;
  clear_has_role_kind();
}
inline ::google::protobuf::uint32 PB_UserLogin::role_kind() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_UserLogin.role_kind)
  return role_kind_;
}
inline void PB_UserLogin::set_role_kind(::google::protobuf::uint32 value) {
  set_has_role_kind();
  role_kind_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_UserLogin.role_kind)
}

// optional uint32 frontend_service_id = 3;
inline bool PB_UserLogin::has_frontend_service_id() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PB_UserLogin::set_has_frontend_service_id() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PB_UserLogin::clear_has_frontend_service_id() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PB_UserLogin::clear_frontend_service_id() {
  frontend_service_id_ = 0u;
  clear_has_frontend_service_id();
}
inline ::google::protobuf::uint32 PB_UserLogin::frontend_service_id() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_UserLogin.frontend_service_id)
  return frontend_service_id_;
}
inline void PB_UserLogin::set_frontend_service_id(::google::protobuf::uint32 value) {
  set_has_frontend_service_id();
  frontend_service_id_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_UserLogin.frontend_service_id)
}

// optional uint32 game_service_id = 4;
inline bool PB_UserLogin::has_game_service_id() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PB_UserLogin::set_has_game_service_id() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PB_UserLogin::clear_has_game_service_id() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PB_UserLogin::clear_game_service_id() {
  game_service_id_ = 0u;
  clear_has_game_service_id();
}
inline ::google::protobuf::uint32 PB_UserLogin::game_service_id() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_UserLogin.game_service_id)
  return game_service_id_;
}
inline void PB_UserLogin::set_game_service_id(::google::protobuf::uint32 value) {
  set_has_game_service_id();
  game_service_id_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_UserLogin.game_service_id)
}

// optional string client_host = 5;
inline bool PB_UserLogin::has_client_host() const {
  return (_has_bits_[0] & 0x00000010u) != 0;
}
inline void PB_UserLogin::set_has_client_host() {
  _has_bits_[0] |= 0x00000010u;
}
inline void PB_UserLogin::clear_has_client_host() {
  _has_bits_[0] &= ~0x00000010u;
}
inline void PB_UserLogin::clear_client_host() {
  if (client_host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_->clear();
  }
  clear_has_client_host();
}
inline const ::std::string& PB_UserLogin::client_host() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_UserLogin.client_host)
  return *client_host_;
}
inline void PB_UserLogin::set_client_host(const ::std::string& value) {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  client_host_->assign(value);
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_UserLogin.client_host)
}
inline void PB_UserLogin::set_client_host(const char* value) {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  client_host_->assign(value);
  // @@protoc_insertion_point(field_set_char:PROTOBUF.PB_UserLogin.client_host)
}
inline void PB_UserLogin::set_client_host(const char* value, size_t size) {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  client_host_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:PROTOBUF.PB_UserLogin.client_host)
}
inline ::std::string* PB_UserLogin::mutable_client_host() {
  set_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    client_host_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:PROTOBUF.PB_UserLogin.client_host)
  return client_host_;
}
inline ::std::string* PB_UserLogin::release_client_host() {
  clear_has_client_host();
  if (client_host_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = client_host_;
    client_host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void PB_UserLogin::set_allocated_client_host(::std::string* client_host) {
  if (client_host_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete client_host_;
  }
  if (client_host) {
    set_has_client_host();
    client_host_ = client_host;
  } else {
    clear_has_client_host();
    client_host_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:PROTOBUF.PB_UserLogin.client_host)
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PROTOBUF

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_msg_5flogin_2eproto__INCLUDED