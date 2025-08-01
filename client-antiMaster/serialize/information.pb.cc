// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: information.proto

#include "information.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

PROTOBUF_CONSTEXPR Information::Information(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.username_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.roomname_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.data1_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.data2_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.data3_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.reqcode_)*/0
  , /*decltype(_impl_.rescode_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct InformationDefaultTypeInternal {
  PROTOBUF_CONSTEXPR InformationDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~InformationDefaultTypeInternal() {}
  union {
    Information _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 InformationDefaultTypeInternal _Information_default_instance_;
static ::_pb::Metadata file_level_metadata_information_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_information_2eproto[2];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_information_2eproto = nullptr;

const uint32_t TableStruct_information_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Information, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.username_),
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.roomname_),
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.data1_),
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.data2_),
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.data3_),
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.reqcode_),
  PROTOBUF_FIELD_OFFSET(::Information, _impl_.rescode_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Information)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::_Information_default_instance_._instance,
};

const char descriptor_table_protodef_information_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021information.proto\"\234\001\n\013Information\022\020\n\010u"
  "serName\030\001 \001(\t\022\020\n\010roomName\030\002 \001(\t\022\r\n\005data1"
  "\030\003 \001(\t\022\r\n\005data2\030\004 \001(\t\022\r\n\005data3\030\005 \001(\t\022\035\n\007"
  "reqcode\030\006 \001(\0162\014.RequestCode\022\035\n\007rescode\030\007"
  " \001(\0162\014.RespondCode*\273\001\n\013RequestCode\022\r\n\tUs"
  "erLogin\020\000\022\014\n\010Register\020\001\022\014\n\010AesFenFa\020\002\022\014\n"
  "\010AutoRoom\020\003\022\016\n\nManualRoom\020\004\022\016\n\nSearchRoo"
  "m\020\005\022\014\n\010GrabLord\020\006\022\r\n\tPlayAHand\020\007\022\014\n\010Game"
  "Over\020\010\022\014\n\010Continue\020\t\022\r\n\tLeaveRoom\020\n\022\013\n\007G"
  "oodbye\020\013*\317\001\n\013RespondCode\022\013\n\007LoginOK\020\000\022\016\n"
  "\nRegisterOK\020\001\022\014\n\010RsaFenFa\020\002\022\017\n\013AesVerify"
  "Ok\020\003\022\016\n\nJoinRoomOK\020\004\022\r\n\tStartGame\020\005\022\020\n\014S"
  "earchRoomOk\020\006\022\r\n\tDealCards\020\007\022\021\n\rOtherGra"
  "bLord\020\010\022\021\n\rOtherPlayHand\020\t\022\022\n\016OtherLeave"
  "Room\020\n\022\n\n\006Failed\020\013b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_information_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_information_2eproto = {
    false, false, 586, descriptor_table_protodef_information_2eproto,
    "information.proto",
    &descriptor_table_information_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_information_2eproto::offsets,
    file_level_metadata_information_2eproto, file_level_enum_descriptors_information_2eproto,
    file_level_service_descriptors_information_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_information_2eproto_getter() {
  return &descriptor_table_information_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_information_2eproto(&descriptor_table_information_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* RequestCode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_information_2eproto);
  return file_level_enum_descriptors_information_2eproto[0];
}
bool RequestCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* RespondCode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_information_2eproto);
  return file_level_enum_descriptors_information_2eproto[1];
}
bool RespondCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Information::_Internal {
 public:
};

Information::Information(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Information)
}
Information::Information(const Information& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Information* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.username_){}
    , decltype(_impl_.roomname_){}
    , decltype(_impl_.data1_){}
    , decltype(_impl_.data2_){}
    , decltype(_impl_.data3_){}
    , decltype(_impl_.reqcode_){}
    , decltype(_impl_.rescode_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.username_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.username_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_username().empty()) {
    _this->_impl_.username_.Set(from._internal_username(), 
      _this->GetArenaForAllocation());
  }
  _impl_.roomname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.roomname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_roomname().empty()) {
    _this->_impl_.roomname_.Set(from._internal_roomname(), 
      _this->GetArenaForAllocation());
  }
  _impl_.data1_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data1_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data1().empty()) {
    _this->_impl_.data1_.Set(from._internal_data1(), 
      _this->GetArenaForAllocation());
  }
  _impl_.data2_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data2_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data2().empty()) {
    _this->_impl_.data2_.Set(from._internal_data2(), 
      _this->GetArenaForAllocation());
  }
  _impl_.data3_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data3_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_data3().empty()) {
    _this->_impl_.data3_.Set(from._internal_data3(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.reqcode_, &from._impl_.reqcode_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.rescode_) -
    reinterpret_cast<char*>(&_impl_.reqcode_)) + sizeof(_impl_.rescode_));
  // @@protoc_insertion_point(copy_constructor:Information)
}

inline void Information::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.username_){}
    , decltype(_impl_.roomname_){}
    , decltype(_impl_.data1_){}
    , decltype(_impl_.data2_){}
    , decltype(_impl_.data3_){}
    , decltype(_impl_.reqcode_){0}
    , decltype(_impl_.rescode_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.username_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.username_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.roomname_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.roomname_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.data1_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data1_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.data2_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data2_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  _impl_.data3_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.data3_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Information::~Information() {
  // @@protoc_insertion_point(destructor:Information)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Information::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.username_.Destroy();
  _impl_.roomname_.Destroy();
  _impl_.data1_.Destroy();
  _impl_.data2_.Destroy();
  _impl_.data3_.Destroy();
}

void Information::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Information::Clear() {
// @@protoc_insertion_point(message_clear_start:Information)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.username_.ClearToEmpty();
  _impl_.roomname_.ClearToEmpty();
  _impl_.data1_.ClearToEmpty();
  _impl_.data2_.ClearToEmpty();
  _impl_.data3_.ClearToEmpty();
  ::memset(&_impl_.reqcode_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.rescode_) -
      reinterpret_cast<char*>(&_impl_.reqcode_)) + sizeof(_impl_.rescode_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Information::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string userName = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_username();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Information.userName"));
        } else
          goto handle_unusual;
        continue;
      // string roomName = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          auto str = _internal_mutable_roomname();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Information.roomName"));
        } else
          goto handle_unusual;
        continue;
      // string data1 = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_data1();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Information.data1"));
        } else
          goto handle_unusual;
        continue;
      // string data2 = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 34)) {
          auto str = _internal_mutable_data2();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Information.data2"));
        } else
          goto handle_unusual;
        continue;
      // string data3 = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          auto str = _internal_mutable_data3();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "Information.data3"));
        } else
          goto handle_unusual;
        continue;
      // .RequestCode reqcode = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_reqcode(static_cast<::RequestCode>(val));
        } else
          goto handle_unusual;
        continue;
      // .RespondCode rescode = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 56)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_rescode(static_cast<::RespondCode>(val));
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* Information::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Information)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string userName = 1;
  if (!this->_internal_username().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_username().data(), static_cast<int>(this->_internal_username().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Information.userName");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_username(), target);
  }

  // string roomName = 2;
  if (!this->_internal_roomname().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_roomname().data(), static_cast<int>(this->_internal_roomname().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Information.roomName");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_roomname(), target);
  }

  // string data1 = 3;
  if (!this->_internal_data1().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data1().data(), static_cast<int>(this->_internal_data1().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Information.data1");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_data1(), target);
  }

  // string data2 = 4;
  if (!this->_internal_data2().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data2().data(), static_cast<int>(this->_internal_data2().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Information.data2");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_data2(), target);
  }

  // string data3 = 5;
  if (!this->_internal_data3().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_data3().data(), static_cast<int>(this->_internal_data3().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "Information.data3");
    target = stream->WriteStringMaybeAliased(
        5, this->_internal_data3(), target);
  }

  // .RequestCode reqcode = 6;
  if (this->_internal_reqcode() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      6, this->_internal_reqcode(), target);
  }

  // .RespondCode rescode = 7;
  if (this->_internal_rescode() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      7, this->_internal_rescode(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Information)
  return target;
}

size_t Information::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Information)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string userName = 1;
  if (!this->_internal_username().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_username());
  }

  // string roomName = 2;
  if (!this->_internal_roomname().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_roomname());
  }

  // string data1 = 3;
  if (!this->_internal_data1().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data1());
  }

  // string data2 = 4;
  if (!this->_internal_data2().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data2());
  }

  // string data3 = 5;
  if (!this->_internal_data3().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_data3());
  }

  // .RequestCode reqcode = 6;
  if (this->_internal_reqcode() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_reqcode());
  }

  // .RespondCode rescode = 7;
  if (this->_internal_rescode() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_rescode());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Information::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Information::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Information::GetClassData() const { return &_class_data_; }


void Information::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Information*>(&to_msg);
  auto& from = static_cast<const Information&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Information)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_username().empty()) {
    _this->_internal_set_username(from._internal_username());
  }
  if (!from._internal_roomname().empty()) {
    _this->_internal_set_roomname(from._internal_roomname());
  }
  if (!from._internal_data1().empty()) {
    _this->_internal_set_data1(from._internal_data1());
  }
  if (!from._internal_data2().empty()) {
    _this->_internal_set_data2(from._internal_data2());
  }
  if (!from._internal_data3().empty()) {
    _this->_internal_set_data3(from._internal_data3());
  }
  if (from._internal_reqcode() != 0) {
    _this->_internal_set_reqcode(from._internal_reqcode());
  }
  if (from._internal_rescode() != 0) {
    _this->_internal_set_rescode(from._internal_rescode());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Information::CopyFrom(const Information& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Information)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Information::IsInitialized() const {
  return true;
}

void Information::InternalSwap(Information* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.username_, lhs_arena,
      &other->_impl_.username_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.roomname_, lhs_arena,
      &other->_impl_.roomname_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.data1_, lhs_arena,
      &other->_impl_.data1_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.data2_, lhs_arena,
      &other->_impl_.data2_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.data3_, lhs_arena,
      &other->_impl_.data3_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Information, _impl_.rescode_)
      + sizeof(Information::_impl_.rescode_)
      - PROTOBUF_FIELD_OFFSET(Information, _impl_.reqcode_)>(
          reinterpret_cast<char*>(&_impl_.reqcode_),
          reinterpret_cast<char*>(&other->_impl_.reqcode_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Information::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_information_2eproto_getter, &descriptor_table_information_2eproto_once,
      file_level_metadata_information_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Information*
Arena::CreateMaybeMessage< ::Information >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Information >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
