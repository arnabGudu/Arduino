#ifndef _ROS_gazebo_ipbot_pid_h
#define _ROS_gazebo_ipbot_pid_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Int16.h"

namespace gazebo_ipbot
{

  class pid : public ros::Msg
  {
    public:
      typedef std_msgs::Int16 _linear_type;
      _linear_type linear;
      typedef std_msgs::Int16 _angular_type;
      _angular_type angular;

    pid():
      linear(),
      angular()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->linear.serialize(outbuffer + offset);
      offset += this->angular.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->linear.deserialize(inbuffer + offset);
      offset += this->angular.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "gazebo_ipbot/pid"; };
    const char * getMD5(){ return "daee48bdd9b022a2534221391301bf32"; };

  };

}
#endif
