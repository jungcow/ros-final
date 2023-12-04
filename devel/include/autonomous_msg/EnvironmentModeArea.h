// Generated by gencpp from file autonomous_msg/EnvironmentModeArea.msg
// DO NOT EDIT!


#ifndef AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTMODEAREA_H
#define AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTMODEAREA_H


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
struct EnvironmentModeArea_
{
  typedef EnvironmentModeArea_<ContainerAllocator> Type;

  EnvironmentModeArea_()
    : ice_x()
    , ice_y()
    , ice_radius()
    , hill_x()
    , hill_y()
    , hill_slope_angle()  {
    }
  EnvironmentModeArea_(const ContainerAllocator& _alloc)
    : ice_x(_alloc)
    , ice_y(_alloc)
    , ice_radius(_alloc)
    , hill_x(_alloc)
    , hill_y(_alloc)
    , hill_slope_angle(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _ice_x_type;
  _ice_x_type ice_x;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _ice_y_type;
  _ice_y_type ice_y;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _ice_radius_type;
  _ice_radius_type ice_radius;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _hill_x_type;
  _hill_x_type hill_x;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _hill_y_type;
  _hill_y_type hill_y;

   typedef std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> _hill_slope_angle_type;
  _hill_slope_angle_type hill_slope_angle;





  typedef boost::shared_ptr< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> const> ConstPtr;

}; // struct EnvironmentModeArea_

typedef ::autonomous_msg::EnvironmentModeArea_<std::allocator<void> > EnvironmentModeArea;

typedef boost::shared_ptr< ::autonomous_msg::EnvironmentModeArea > EnvironmentModeAreaPtr;
typedef boost::shared_ptr< ::autonomous_msg::EnvironmentModeArea const> EnvironmentModeAreaConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator1> & lhs, const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator2> & rhs)
{
  return lhs.ice_x == rhs.ice_x &&
    lhs.ice_y == rhs.ice_y &&
    lhs.ice_radius == rhs.ice_radius &&
    lhs.hill_x == rhs.hill_x &&
    lhs.hill_y == rhs.hill_y &&
    lhs.hill_slope_angle == rhs.hill_slope_angle;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator1> & lhs, const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autonomous_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
{
  static const char* value()
  {
    return "aa04ea7b504bc5eedff12056d464548d";
  }

  static const char* value(const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0xaa04ea7b504bc5eeULL;
  static const uint64_t static_value2 = 0xdff12056d464548dULL;
};

template<class ContainerAllocator>
struct DataType< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autonomous_msg/EnvironmentModeArea";
  }

  static const char* value(const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
{
  static const char* value()
  {
    return "float64[] ice_x\n"
"float64[] ice_y\n"
"float64[] ice_radius\n"
"float64[] hill_x\n"
"float64[] hill_y\n"
"float64[] hill_slope_angle\n"
;
  }

  static const char* value(const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.ice_x);
      stream.next(m.ice_y);
      stream.next(m.ice_radius);
      stream.next(m.hill_x);
      stream.next(m.hill_y);
      stream.next(m.hill_slope_angle);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct EnvironmentModeArea_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autonomous_msg::EnvironmentModeArea_<ContainerAllocator>& v)
  {
    s << indent << "ice_x[]" << std::endl;
    for (size_t i = 0; i < v.ice_x.size(); ++i)
    {
      s << indent << "  ice_x[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.ice_x[i]);
    }
    s << indent << "ice_y[]" << std::endl;
    for (size_t i = 0; i < v.ice_y.size(); ++i)
    {
      s << indent << "  ice_y[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.ice_y[i]);
    }
    s << indent << "ice_radius[]" << std::endl;
    for (size_t i = 0; i < v.ice_radius.size(); ++i)
    {
      s << indent << "  ice_radius[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.ice_radius[i]);
    }
    s << indent << "hill_x[]" << std::endl;
    for (size_t i = 0; i < v.hill_x.size(); ++i)
    {
      s << indent << "  hill_x[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.hill_x[i]);
    }
    s << indent << "hill_y[]" << std::endl;
    for (size_t i = 0; i < v.hill_y.size(); ++i)
    {
      s << indent << "  hill_y[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.hill_y[i]);
    }
    s << indent << "hill_slope_angle[]" << std::endl;
    for (size_t i = 0; i < v.hill_slope_angle.size(); ++i)
    {
      s << indent << "  hill_slope_angle[" << i << "]: ";
      Printer<double>::stream(s, indent + "  ", v.hill_slope_angle[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTONOMOUS_MSG_MESSAGE_ENVIRONMENTMODEAREA_H
