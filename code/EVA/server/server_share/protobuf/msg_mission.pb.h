// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg_mission.proto

#ifndef PROTOBUF_msg_5fmission_2eproto__INCLUDED
#define PROTOBUF_msg_5fmission_2eproto__INCLUDED

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
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace PROTOBUF {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_msg_5fmission_2eproto();
void protobuf_AssignDesc_msg_5fmission_2eproto();
void protobuf_ShutdownFile_msg_5fmission_2eproto();

class PB_Mission;
class PB_MissionList;

enum PB_TMissionState {
  MISSION_STATE_INVALID = 0,
  MISSION_STATE_ACCEPT = 1,
  MISSION_STATE_DONE = 2,
  MISSION_STATE_REWARD = 3,
  MISSION_STATE_CLOSE = 4
};
bool PB_TMissionState_IsValid(int value);
const PB_TMissionState PB_TMissionState_MIN = MISSION_STATE_INVALID;
const PB_TMissionState PB_TMissionState_MAX = MISSION_STATE_CLOSE;
const int PB_TMissionState_ARRAYSIZE = PB_TMissionState_MAX + 1;

const ::google::protobuf::EnumDescriptor* PB_TMissionState_descriptor();
inline const ::std::string& PB_TMissionState_Name(PB_TMissionState value) {
  return ::google::protobuf::internal::NameOfEnum(
    PB_TMissionState_descriptor(), value);
}
inline bool PB_TMissionState_Parse(
    const ::std::string& name, PB_TMissionState* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PB_TMissionState>(
    PB_TMissionState_descriptor(), name, value);
}
// ===================================================================

class PB_Mission : public ::google::protobuf::Message {
 public:
  PB_Mission();
  virtual ~PB_Mission();

  PB_Mission(const PB_Mission& from);

  inline PB_Mission& operator=(const PB_Mission& from) {
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
  static const PB_Mission& default_instance();

  void Swap(PB_Mission* other);

  // implements Message ----------------------------------------------

  PB_Mission* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PB_Mission& from);
  void MergeFrom(const PB_Mission& from);
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

  // optional uint32 mission_id = 1;
  inline bool has_mission_id() const;
  inline void clear_mission_id();
  static const int kMissionIdFieldNumber = 1;
  inline ::google::protobuf::uint32 mission_id() const;
  inline void set_mission_id(::google::protobuf::uint32 value);

  // optional uint32 mission_state = 2;
  inline bool has_mission_state() const;
  inline void clear_mission_state();
  static const int kMissionStateFieldNumber = 2;
  inline ::google::protobuf::uint32 mission_state() const;
  inline void set_mission_state(::google::protobuf::uint32 value);

  // optional uint32 mission_target = 3;
  inline bool has_mission_target() const;
  inline void clear_mission_target();
  static const int kMissionTargetFieldNumber = 3;
  inline ::google::protobuf::uint32 mission_target() const;
  inline void set_mission_target(::google::protobuf::uint32 value);

  // optional uint32 mission_receive_time = 4;
  inline bool has_mission_receive_time() const;
  inline void clear_mission_receive_time();
  static const int kMissionReceiveTimeFieldNumber = 4;
  inline ::google::protobuf::uint32 mission_receive_time() const;
  inline void set_mission_receive_time(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:PROTOBUF.PB_Mission)
 private:
  inline void set_has_mission_id();
  inline void clear_has_mission_id();
  inline void set_has_mission_state();
  inline void clear_has_mission_state();
  inline void set_has_mission_target();
  inline void clear_has_mission_target();
  inline void set_has_mission_receive_time();
  inline void clear_has_mission_receive_time();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::uint32 mission_id_;
  ::google::protobuf::uint32 mission_state_;
  ::google::protobuf::uint32 mission_target_;
  ::google::protobuf::uint32 mission_receive_time_;
  friend void  protobuf_AddDesc_msg_5fmission_2eproto();
  friend void protobuf_AssignDesc_msg_5fmission_2eproto();
  friend void protobuf_ShutdownFile_msg_5fmission_2eproto();

  void InitAsDefaultInstance();
  static PB_Mission* default_instance_;
};
// -------------------------------------------------------------------

class PB_MissionList : public ::google::protobuf::Message {
 public:
  PB_MissionList();
  virtual ~PB_MissionList();

  PB_MissionList(const PB_MissionList& from);

  inline PB_MissionList& operator=(const PB_MissionList& from) {
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
  static const PB_MissionList& default_instance();

  void Swap(PB_MissionList* other);

  // implements Message ----------------------------------------------

  PB_MissionList* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const PB_MissionList& from);
  void MergeFrom(const PB_MissionList& from);
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

  // repeated .PROTOBUF.PB_Mission mission_list = 1;
  inline int mission_list_size() const;
  inline void clear_mission_list();
  static const int kMissionListFieldNumber = 1;
  inline const ::PROTOBUF::PB_Mission& mission_list(int index) const;
  inline ::PROTOBUF::PB_Mission* mutable_mission_list(int index);
  inline ::PROTOBUF::PB_Mission* add_mission_list();
  inline const ::google::protobuf::RepeatedPtrField< ::PROTOBUF::PB_Mission >&
      mission_list() const;
  inline ::google::protobuf::RepeatedPtrField< ::PROTOBUF::PB_Mission >*
      mutable_mission_list();

  // @@protoc_insertion_point(class_scope:PROTOBUF.PB_MissionList)
 private:

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::RepeatedPtrField< ::PROTOBUF::PB_Mission > mission_list_;
  friend void  protobuf_AddDesc_msg_5fmission_2eproto();
  friend void protobuf_AssignDesc_msg_5fmission_2eproto();
  friend void protobuf_ShutdownFile_msg_5fmission_2eproto();

  void InitAsDefaultInstance();
  static PB_MissionList* default_instance_;
};
// ===================================================================


// ===================================================================

// PB_Mission

// optional uint32 mission_id = 1;
inline bool PB_Mission::has_mission_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void PB_Mission::set_has_mission_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void PB_Mission::clear_has_mission_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void PB_Mission::clear_mission_id() {
  mission_id_ = 0u;
  clear_has_mission_id();
}
inline ::google::protobuf::uint32 PB_Mission::mission_id() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_Mission.mission_id)
  return mission_id_;
}
inline void PB_Mission::set_mission_id(::google::protobuf::uint32 value) {
  set_has_mission_id();
  mission_id_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_Mission.mission_id)
}

// optional uint32 mission_state = 2;
inline bool PB_Mission::has_mission_state() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void PB_Mission::set_has_mission_state() {
  _has_bits_[0] |= 0x00000002u;
}
inline void PB_Mission::clear_has_mission_state() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void PB_Mission::clear_mission_state() {
  mission_state_ = 0u;
  clear_has_mission_state();
}
inline ::google::protobuf::uint32 PB_Mission::mission_state() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_Mission.mission_state)
  return mission_state_;
}
inline void PB_Mission::set_mission_state(::google::protobuf::uint32 value) {
  set_has_mission_state();
  mission_state_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_Mission.mission_state)
}

// optional uint32 mission_target = 3;
inline bool PB_Mission::has_mission_target() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void PB_Mission::set_has_mission_target() {
  _has_bits_[0] |= 0x00000004u;
}
inline void PB_Mission::clear_has_mission_target() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void PB_Mission::clear_mission_target() {
  mission_target_ = 0u;
  clear_has_mission_target();
}
inline ::google::protobuf::uint32 PB_Mission::mission_target() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_Mission.mission_target)
  return mission_target_;
}
inline void PB_Mission::set_mission_target(::google::protobuf::uint32 value) {
  set_has_mission_target();
  mission_target_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_Mission.mission_target)
}

// optional uint32 mission_receive_time = 4;
inline bool PB_Mission::has_mission_receive_time() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void PB_Mission::set_has_mission_receive_time() {
  _has_bits_[0] |= 0x00000008u;
}
inline void PB_Mission::clear_has_mission_receive_time() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void PB_Mission::clear_mission_receive_time() {
  mission_receive_time_ = 0u;
  clear_has_mission_receive_time();
}
inline ::google::protobuf::uint32 PB_Mission::mission_receive_time() const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_Mission.mission_receive_time)
  return mission_receive_time_;
}
inline void PB_Mission::set_mission_receive_time(::google::protobuf::uint32 value) {
  set_has_mission_receive_time();
  mission_receive_time_ = value;
  // @@protoc_insertion_point(field_set:PROTOBUF.PB_Mission.mission_receive_time)
}

// -------------------------------------------------------------------

// PB_MissionList

// repeated .PROTOBUF.PB_Mission mission_list = 1;
inline int PB_MissionList::mission_list_size() const {
  return mission_list_.size();
}
inline void PB_MissionList::clear_mission_list() {
  mission_list_.Clear();
}
inline const ::PROTOBUF::PB_Mission& PB_MissionList::mission_list(int index) const {
  // @@protoc_insertion_point(field_get:PROTOBUF.PB_MissionList.mission_list)
  return mission_list_.Get(index);
}
inline ::PROTOBUF::PB_Mission* PB_MissionList::mutable_mission_list(int index) {
  // @@protoc_insertion_point(field_mutable:PROTOBUF.PB_MissionList.mission_list)
  return mission_list_.Mutable(index);
}
inline ::PROTOBUF::PB_Mission* PB_MissionList::add_mission_list() {
  // @@protoc_insertion_point(field_add:PROTOBUF.PB_MissionList.mission_list)
  return mission_list_.Add();
}
inline const ::google::protobuf::RepeatedPtrField< ::PROTOBUF::PB_Mission >&
PB_MissionList::mission_list() const {
  // @@protoc_insertion_point(field_list:PROTOBUF.PB_MissionList.mission_list)
  return mission_list_;
}
inline ::google::protobuf::RepeatedPtrField< ::PROTOBUF::PB_Mission >*
PB_MissionList::mutable_mission_list() {
  // @@protoc_insertion_point(field_mutable_list:PROTOBUF.PB_MissionList.mission_list)
  return &mission_list_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace PROTOBUF

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::PROTOBUF::PB_TMissionState> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::PROTOBUF::PB_TMissionState>() {
  return ::PROTOBUF::PB_TMissionState_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_msg_5fmission_2eproto__INCLUDED
