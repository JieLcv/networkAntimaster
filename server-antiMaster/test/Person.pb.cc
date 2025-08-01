// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Person.proto

#include "Person.pb.h"

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

namespace Erbing {
PROTOBUF_CONSTEXPR Person::Person(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.name_)*/{}
  , /*decltype(_impl_.sex_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.addr_)*/nullptr
  , /*decltype(_impl_.id_)*/0
  , /*decltype(_impl_.age_)*/0
  , /*decltype(_impl_.color_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PersonDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PersonDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PersonDefaultTypeInternal() {}
  union {
    Person _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PersonDefaultTypeInternal _Person_default_instance_;
}  // namespace Erbing
static ::_pb::Metadata file_level_metadata_Person_2eproto[1];
static const ::_pb::EnumDescriptor* file_level_enum_descriptors_Person_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_Person_2eproto = nullptr;

const uint32_t TableStruct_Person_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _impl_.id_),
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _impl_.name_),
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _impl_.sex_),
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _impl_.age_),
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _impl_.addr_),
  PROTOBUF_FIELD_OFFSET(::Erbing::Person, _impl_.color_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Erbing::Person)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Erbing::_Person_default_instance_._instance,
};

const char descriptor_table_protodef_Person_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\014Person.proto\022\006Erbing\032\rAddress.proto\"y\n"
  "\006Person\022\n\n\002id\030\001 \001(\005\022\014\n\004name\030\002 \003(\014\022\013\n\003sex"
  "\030\003 \001(\014\022\013\n\003age\030\004 \001(\005\022\035\n\004addr\030\005 \001(\0132\017.Dabi"
  "ng.Address\022\034\n\005color\030\006 \001(\0162\r.Erbing.Color"
  "*1\n\005Color\022\007\n\003Red\020\000\022\t\n\005Green\020\003\022\n\n\006Yellow\020"
  "\006\022\010\n\004Blue\020\tb\006proto3"
  ;
static const ::_pbi::DescriptorTable* const descriptor_table_Person_2eproto_deps[1] = {
  &::descriptor_table_Address_2eproto,
};
static ::_pbi::once_flag descriptor_table_Person_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_Person_2eproto = {
    false, false, 219, descriptor_table_protodef_Person_2eproto,
    "Person.proto",
    &descriptor_table_Person_2eproto_once, descriptor_table_Person_2eproto_deps, 1, 1,
    schemas, file_default_instances, TableStruct_Person_2eproto::offsets,
    file_level_metadata_Person_2eproto, file_level_enum_descriptors_Person_2eproto,
    file_level_service_descriptors_Person_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_Person_2eproto_getter() {
  return &descriptor_table_Person_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_Person_2eproto(&descriptor_table_Person_2eproto);
namespace Erbing {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Color_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_Person_2eproto);
  return file_level_enum_descriptors_Person_2eproto[0];
}
bool Color_IsValid(int value) {
  switch (value) {
    case 0:
    case 3:
    case 6:
    case 9:
      return true;
    default:
      return false;
  }
}


// ===================================================================

class Person::_Internal {
 public:
  static const ::Dabing::Address& addr(const Person* msg);
};

const ::Dabing::Address&
Person::_Internal::addr(const Person* msg) {
  return *msg->_impl_.addr_;
}
void Person::clear_addr() {
  if (GetArenaForAllocation() == nullptr && _impl_.addr_ != nullptr) {
    delete _impl_.addr_;
  }
  _impl_.addr_ = nullptr;
}
Person::Person(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Erbing.Person)
}
Person::Person(const Person& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  Person* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){from._impl_.name_}
    , decltype(_impl_.sex_){}
    , decltype(_impl_.addr_){nullptr}
    , decltype(_impl_.id_){}
    , decltype(_impl_.age_){}
    , decltype(_impl_.color_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.sex_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.sex_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_sex().empty()) {
    _this->_impl_.sex_.Set(from._internal_sex(), 
      _this->GetArenaForAllocation());
  }
  if (from._internal_has_addr()) {
    _this->_impl_.addr_ = new ::Dabing::Address(*from._impl_.addr_);
  }
  ::memcpy(&_impl_.id_, &from._impl_.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.color_) -
    reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.color_));
  // @@protoc_insertion_point(copy_constructor:Erbing.Person)
}

inline void Person::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.name_){arena}
    , decltype(_impl_.sex_){}
    , decltype(_impl_.addr_){nullptr}
    , decltype(_impl_.id_){0}
    , decltype(_impl_.age_){0}
    , decltype(_impl_.color_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.sex_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.sex_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

Person::~Person() {
  // @@protoc_insertion_point(destructor:Erbing.Person)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void Person::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.name_.~RepeatedPtrField();
  _impl_.sex_.Destroy();
  if (this != internal_default_instance()) delete _impl_.addr_;
}

void Person::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void Person::Clear() {
// @@protoc_insertion_point(message_clear_start:Erbing.Person)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.name_.Clear();
  _impl_.sex_.ClearToEmpty();
  if (GetArenaForAllocation() == nullptr && _impl_.addr_ != nullptr) {
    delete _impl_.addr_;
  }
  _impl_.addr_ = nullptr;
  ::memset(&_impl_.id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.color_) -
      reinterpret_cast<char*>(&_impl_.id_)) + sizeof(_impl_.color_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* Person::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // repeated bytes name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            auto str = _internal_add_name();
            ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else
          goto handle_unusual;
        continue;
      // bytes sex = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 26)) {
          auto str = _internal_mutable_sex();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 age = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 32)) {
          _impl_.age_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .Dabing.Address addr = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 42)) {
          ptr = ctx->ParseMessage(_internal_mutable_addr(), ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // .Erbing.Color color = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 48)) {
          uint64_t val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_color(static_cast<::Erbing::Color>(val));
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

uint8_t* Person::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Erbing.Person)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_id(), target);
  }

  // repeated bytes name = 2;
  for (int i = 0, n = this->_internal_name_size(); i < n; i++) {
    const auto& s = this->_internal_name(i);
    target = stream->WriteBytes(2, s, target);
  }

  // bytes sex = 3;
  if (!this->_internal_sex().empty()) {
    target = stream->WriteBytesMaybeAliased(
        3, this->_internal_sex(), target);
  }

  // int32 age = 4;
  if (this->_internal_age() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(4, this->_internal_age(), target);
  }

  // .Dabing.Address addr = 5;
  if (this->_internal_has_addr()) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(5, _Internal::addr(this),
        _Internal::addr(this).GetCachedSize(), target, stream);
  }

  // .Erbing.Color color = 6;
  if (this->_internal_color() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteEnumToArray(
      6, this->_internal_color(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Erbing.Person)
  return target;
}

size_t Person::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Erbing.Person)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated bytes name = 2;
  total_size += 1 *
      ::PROTOBUF_NAMESPACE_ID::internal::FromIntSize(_impl_.name_.size());
  for (int i = 0, n = _impl_.name_.size(); i < n; i++) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
      _impl_.name_.Get(i));
  }

  // bytes sex = 3;
  if (!this->_internal_sex().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_sex());
  }

  // .Dabing.Address addr = 5;
  if (this->_internal_has_addr()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *_impl_.addr_);
  }

  // int32 id = 1;
  if (this->_internal_id() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_id());
  }

  // int32 age = 4;
  if (this->_internal_age() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_age());
  }

  // .Erbing.Color color = 6;
  if (this->_internal_color() != 0) {
    total_size += 1 +
      ::_pbi::WireFormatLite::EnumSize(this->_internal_color());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData Person::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    Person::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*Person::GetClassData() const { return &_class_data_; }


void Person::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<Person*>(&to_msg);
  auto& from = static_cast<const Person&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Erbing.Person)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  _this->_impl_.name_.MergeFrom(from._impl_.name_);
  if (!from._internal_sex().empty()) {
    _this->_internal_set_sex(from._internal_sex());
  }
  if (from._internal_has_addr()) {
    _this->_internal_mutable_addr()->::Dabing::Address::MergeFrom(
        from._internal_addr());
  }
  if (from._internal_id() != 0) {
    _this->_internal_set_id(from._internal_id());
  }
  if (from._internal_age() != 0) {
    _this->_internal_set_age(from._internal_age());
  }
  if (from._internal_color() != 0) {
    _this->_internal_set_color(from._internal_color());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void Person::CopyFrom(const Person& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Erbing.Person)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Person::IsInitialized() const {
  return true;
}

void Person::InternalSwap(Person* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  _impl_.name_.InternalSwap(&other->_impl_.name_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.sex_, lhs_arena,
      &other->_impl_.sex_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(Person, _impl_.color_)
      + sizeof(Person::_impl_.color_)
      - PROTOBUF_FIELD_OFFSET(Person, _impl_.addr_)>(
          reinterpret_cast<char*>(&_impl_.addr_),
          reinterpret_cast<char*>(&other->_impl_.addr_));
}

::PROTOBUF_NAMESPACE_ID::Metadata Person::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_Person_2eproto_getter, &descriptor_table_Person_2eproto_once,
      file_level_metadata_Person_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Erbing
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Erbing::Person*
Arena::CreateMaybeMessage< ::Erbing::Person >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Erbing::Person >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
