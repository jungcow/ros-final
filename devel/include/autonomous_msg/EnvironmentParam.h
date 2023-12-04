// Generated by gencpp from file autonomous_msg/EnvironmentParam.msg
// DO NOT EDIT!


#ifndef AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTPARAM_H
#define AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTPARAM_H


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
struct EnvironmentParam_
{
  typedef EnvironmentParam_<ContainerAllocator> Type;

  EnvironmentParam_()
    : fyf_max(0.0)
    , fyr_max(0.0)
    , slope_angle(0.0)  {
    }
  EnvironmentParam_(const ContainerAllocator& _alloc)
    : fyf_max(0.0)
    , fyr_max(0.0)
    , slope_angle(0.0)  {
  (void)_alloc;
    }



   typedef double _fyf_max_type;
  _fyf_max_type fyf_max;

   typedef double _fyr_max_type;
  _fyr_max_type fyr_max;

   typedef double _slope_angle_type;
  _slope_angle_type slope_angle;





  typedef boost::shared_ptr< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> const> ConstPtr;

}; // struct EnvironmentParam_

typedef ::autonomous_msg::EnvironmentParam_<std::allocator<void> > EnvironmentParam;

typedef boost::shared_ptr< ::autonomous_msg::EnvironmentParam > EnvironmentParamPtr;
typedef boost::shared_ptr< ::autonomous_msg::EnvironmentParam const> EnvironmentParamConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autonomous_msg::EnvironmentParam_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autonomous_msg::EnvironmentParam_<ContainerAllocator1> & lhs, const ::autonomous_msg::EnvironmentParam_<ContainerAllocator2> & rhs)
{
  return lhs.fyf_max == rhs.fyf_max &&
    lhs.fyr_max == rhs.fyr_max &&
    lhs.slope_angle == rhs.slope_angle;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autonomous_msg::EnvironmentParam_<ContainerAllocator1> & lhs, const ::autonomous_msg::EnvironmentParam_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autonomous_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
{
  static const char* value()
  {
    return "f757b3e255dfef4f680d3558f78ceb06";
  }

  static const char* value(const ::autonomous_msg::EnvironmentParam_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xf757b3e255dfef4fULL;
  static const uint64_t static_value2 = 0x680d3558f78ceb06ULL;
};

template<class ContainerAllocator>
struct DataType< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autonomous_msg/EnvironmentParam";
  }

  static const char* value(const ::autonomous_msg::EnvironmentParam_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 fyf_max\n"
"float64 fyr_max\n"
"float64 slope_angle\n"
;
  }

  static const char* value(const ::autonomous_msg::EnvironmentParam_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.fyf_max);
      stream.next(m.fyr_max);
      stream.next(m.slope_angle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct EnvironmentParam_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autonomous_msg::EnvironmentParam_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autonomous_msg::EnvironmentParam_<ContainerAllocator>& v)
  {
    s << indent << "fyf_max: ";
    Printer<double>::stream(s, indent + "  ", v.fyf_max);
    s << indent << "fyr_max: ";
    Printer<double>::stream(s, indent + "  ", v.fyr_max);
    s << indent << "slope_angle: ";
    Printer<double>::stream(s, indent + "  ", v.slope_angle);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTPARAM_H