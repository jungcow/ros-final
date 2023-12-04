// Generated by gencpp from file autonomous_msg/VehicleOutputs.msg
// DO NOT EDIT!


#ifndef AUTONOMOUS_MSG_MESSAGE_VEHICLEOUTPUTS_H
#define AUTONOMOUS_MSG_MESSAGE_VEHICLEOUTPUTS_H


#include <string>
#include <vector>
#include <memory>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <autonomous_msg/VehicleOutput.h>

namespace autonomous_msg
{
template <class ContainerAllocator>
struct VehicleOutputs_
{
  typedef VehicleOutputs_<ContainerAllocator> Type;

  VehicleOutputs_()
    : vehicleOuputs()  {
    }
  VehicleOutputs_(const ContainerAllocator& _alloc)
    : vehicleOuputs(_alloc)  {
  (void)_alloc;
    }



   typedef std::vector< ::autonomous_msg::VehicleOutput_<ContainerAllocator> , typename std::allocator_traits<ContainerAllocator>::template rebind_alloc< ::autonomous_msg::VehicleOutput_<ContainerAllocator> >> _vehicleOuputs_type;
  _vehicleOuputs_type vehicleOuputs;





  typedef boost::shared_ptr< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> const> ConstPtr;

}; // struct VehicleOutputs_

typedef ::autonomous_msg::VehicleOutputs_<std::allocator<void> > VehicleOutputs;

typedef boost::shared_ptr< ::autonomous_msg::VehicleOutputs > VehicleOutputsPtr;
typedef boost::shared_ptr< ::autonomous_msg::VehicleOutputs const> VehicleOutputsConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::autonomous_msg::VehicleOutputs_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::autonomous_msg::VehicleOutputs_<ContainerAllocator1> & lhs, const ::autonomous_msg::VehicleOutputs_<ContainerAllocator2> & rhs)
{
  return lhs.vehicleOuputs == rhs.vehicleOuputs;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::autonomous_msg::VehicleOutputs_<ContainerAllocator1> & lhs, const ::autonomous_msg::VehicleOutputs_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace autonomous_msg

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> const>
  : FalseType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "1f3e123ab591600bc0713eeba94ade0a";
  }

  static const char* value(const ::autonomous_msg::VehicleOutputs_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x1f3e123ab591600bULL;
  static const uint64_t static_value2 = 0xc0713eeba94ade0aULL;
};

template<class ContainerAllocator>
struct DataType< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "autonomous_msg/VehicleOutputs";
  }

  static const char* value(const ::autonomous_msg::VehicleOutputs_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
{
  static const char* value()
  {
    return "VehicleOutput[] vehicleOuputs\n"
"================================================================================\n"
"MSG: autonomous_msg/VehicleOutput\n"
"string id \n"
"float64 x\n"
"float64 y\n"
"float64 yaw\n"
"float64 velocity\n"
"float64 length\n"
"float64 width\n"
;
  }

  static const char* value(const ::autonomous_msg::VehicleOutputs_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.vehicleOuputs);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct VehicleOutputs_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::autonomous_msg::VehicleOutputs_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::autonomous_msg::VehicleOutputs_<ContainerAllocator>& v)
  {
    s << indent << "vehicleOuputs[]" << std::endl;
    for (size_t i = 0; i < v.vehicleOuputs.size(); ++i)
    {
      s << indent << "  vehicleOuputs[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::autonomous_msg::VehicleOutput_<ContainerAllocator> >::stream(s, indent + "    ", v.vehicleOuputs[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // AUTONOMOUS_MSG_MESSAGE_VEHICLEOUTPUTS_H
