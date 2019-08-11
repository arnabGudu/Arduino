#ifndef _ROS_gazebo_ipbot_tuning_h
#define _ROS_gazebo_ipbot_tuning_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Int16.h"

namespace gazebo_ipbot
{

  class tuning : public ros::Msg
  {
    public:
      typedef std_msgs::Int16 _lkp_type;
      _lkp_type lkp;
      typedef std_msgs::Int16 _lkd_type;
      _lkd_type lkd;
      typedef std_msgs::Int16 _lki_type;
      _lki_type lki;
      typedef std_msgs::Int16 _akp_type;
      _akp_type akp;
      typedef std_msgs::Int16 _akd_type;
      _akd_type akd;
      typedef std_msgs::Int16 _aki_type;
      _aki_type aki;
      typedef std_msgs::Int16 _vel_type;
      _vel_type vel;

    tuning():
      lkp(),
      lkd(),
      lki(),
      akp(),
      akd(),
      aki(),
      vel()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->lkp.serialize(outbuffer + offset);
      offset += this->lkd.serialize(outbuffer + offset);
      offset += this->lki.serialize(outbuffer + offset);
      offset += this->akp.serialize(outbuffer + offset);
      offset += this->akd.serialize(outbuffer + offset);
      offset += this->aki.serialize(outbuffer + offset);
      offset += this->vel.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->lkp.deserialize(inbuffer + offset);
      offset += this->lkd.deserialize(inbuffer + offset);
      offset += this->lki.deserialize(inbuffer + offset);
      offset += this->akp.deserialize(inbuffer + offset);
      offset += this->akd.deserialize(inbuffer + offset);
      offset += this->aki.deserialize(inbuffer + offset);
      offset += this->vel.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "gazebo_ipbot/tuning"; };
    const char * getMD5(){ return "8cd8aa6abc2468ca69bf190c916f0446"; };

  };

}
#endif
