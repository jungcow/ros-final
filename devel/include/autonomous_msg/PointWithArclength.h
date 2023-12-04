// Generated by gencpp from file autonomous_msg/PointWithArclength.msg
// DO NOT EDIT!


#ifndef AUTONOMOUS_MSG_MESSAGE_POINTWITHARCLENGTH_H
#define AUTONOMOUS_MSG_MESSAGE_POINTWITHARCLENGTH_H


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
struct PointWithArclength_
{
  typedef PointWithArclength_<ContainerAllocator> Type;

  PointWithArclength_()
    : x(0.0)
    , y(0.0)
    , arclength(0.0)  {
    }
  PointWithArclength_(const ContainerAllocator& _alloc)
    : x(0.0)
    , y(0.0)
    , arclength(0.0)  {
  (void)_alloc;
    }



   typedef double _x_type;
  _x_type x;

   typedef double _y_type;
  _y_type y;

   typedef double _arclength_type;
  _arclength_type arclength;





  typedef boost::shared_ptr< ::autonomous_msg::PointWithArclength_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autonomous_msg::PointWithArclength_<ContainerAllocator> const> ConstPtr;

}; // struct PointWithArclength_

typedef ::autonomous_msg::PointWithArclength_<std::allocator<void> > PointWithArclength;

typedef boost::shared_ptr< ::autonomous_msg::PointWithArclength > PointWithArclengthPtr;
typedef boost::shared_ptr< ::autonomous_msg::PointWithArclength const> PointWithArclengthConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autonomous_msg::PointWithArclength_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autonomous_msg::PointWithArclength_<ContainerAllocator1> & lhs, const ::autonomous_msg::PointWithArclength_<ContainerAllocator2> & rhs)
{
  return lhs.x == rhs.x &&
    lhs.y == rhs.y &&
    lhs.arclength == rhs.arclength;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autonomous_msg::PointWithArclength_<ContainerAllocator1> & lhs, const ::autonomous_msg::PointWithArclength_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autonomous_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::PointWithArclength_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::PointWithArclength_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::PointWithArclength_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
{
  static const char* value()
  {
    return "c506beb715b61f42d987dcfd7000dedb";
  }

  static const char* value(const ::autonomous_msg::PointWithArclength_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xc506beb715b61f42ULL;
  static const uint64_t static_value2 = 0xd987dcfd7000dedbULL;
};

template<class ContainerAllocator>
struct DataType< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autonomous_msg/PointWithArclength";
  }

  static const char* value(const ::autonomous_msg::PointWithArclength_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64 x\n"
"float64 y\n"
"float64 arclength\n"
;
  }

  static const char* value(const ::autonomous_msg::PointWithArclength_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.x);
      stream.next(m.y);
      stream.next(m.arclength);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct PointWithArclength_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autonomous_msg::PointWithArclength_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autonomous_msg::PointWithArclength_<ContainerAllocator>& v)
  {
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "arclength: ";
    Printer<double>::stream(s, indent + "  ", v.arclength);
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTONOMOUS_MSG_MESSAGE_POINTWITHARCLENGTH_H
