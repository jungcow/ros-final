// Generated by gencpp from file autonomous_msg/EnvironmentMode.msg
// DO NOT EDIT!


#ifndef AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTMODE_H
#define AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTMODE_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>


namespace autonomous_msg
{
template <class ContainerAllocator>
struct EnvironmentMode_
{
  typedef EnvironmentMode_<ContainerAllocator> Type;

  EnvironmentMode_()
    : ice_mode()
    , hill_mode()  {
    }
  EnvironmentMode_(const ContainerAllocator& _alloc)
    : ice_mode(_alloc)
    , hill_mode(_alloc)  {
  (void)_alloc;
    }



   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _ice_mode_type;
  _ice_mode_type ice_mode;

   typedef std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> _hill_mode_type;
  _hill_mode_type hill_mode;





  typedef boost::shared_ptr< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> const> ConstPtr;

}; // struct EnvironmentMode_

typedef ::autonomous_msg::EnvironmentMode_<std::allocator<void> > EnvironmentMode;

typedef boost::shared_ptr< ::autonomous_msg::EnvironmentMode > EnvironmentModePtr;
typedef boost::shared_ptr< ::autonomous_msg::EnvironmentMode const> EnvironmentModeConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autonomous_msg::EnvironmentMode_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autonomous_msg::EnvironmentMode_<ContainerAllocator1> & lhs, const ::autonomous_msg::EnvironmentMode_<ContainerAllocator2> & rhs)
{
  return lhs.ice_mode == rhs.ice_mode &&
    lhs.hill_mode == rhs.hill_mode;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autonomous_msg::EnvironmentMode_<ContainerAllocator1> & lhs, const ::autonomous_msg::EnvironmentMode_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autonomous_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
{
  static const char* value()
  {
    return "df53af7b00c9079615c2b52e2721e823";
  }

  static const char* value(const ::autonomous_msg::EnvironmentMode_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xdf53af7b00c90796ULL;
  static const uint64_t static_value2 = 0x15c2b52e2721e823ULL;
};

template<class ContainerAllocator>
struct DataType< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autonomous_msg/EnvironmentMode";
  }

  static const char* value(const ::autonomous_msg::EnvironmentMode_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
{
  static const char* value()
  {
    return "string ice_mode\n"
"string hill_mode\n"
;
  }

  static const char* value(const ::autonomous_msg::EnvironmentMode_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ice_mode);
      stream.next(m.hill_mode);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct EnvironmentMode_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autonomous_msg::EnvironmentMode_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autonomous_msg::EnvironmentMode_<ContainerAllocator>& v)
  {
    s << indent << "ice_mode: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.ice_mode);
    s << indent << "hill_mode: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>::stream(s, indent + "  ", v.hill_mode);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTMODE_H