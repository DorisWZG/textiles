// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __IN_SR_PORT_HPP__
#define __IN_SR_PORT_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <stdlib.h>

#include <kdl/frames.hpp>

#define VOCAB_GO VOCAB2('g','o')
#define VOCAB_MOVJ VOCAB4('m','o','v','j')
#define VOCAB_STAT VOCAB4('s','t','a','t')

#define DEFAULT_JOINT_VELS 2.0

#define GRIPPER_OPEN 0
#define GRIPPER_CLOSE 1

// thanks! https://web.stanford.edu/~qianyizh/projects/scenedata.html
#define DEFAULT_FX_D          525.0  // 640x480
#define DEFAULT_FY_D          525.0  //
#define DEFAULT_CX_D          319.5  //
#define DEFAULT_CY_D          239.5  //
#define DEFAULT_FX_RGB        525.0  //
#define DEFAULT_FY_RGB        525.0  //
#define DEFAULT_CX_RGB        319.5  //
#define DEFAULT_CY_RGB        239.5  //

using namespace yarp::os;

namespace teo
{

/**
 * @ingroup mover
 *
 * @brief Input port of speech recognition data.
 *
 */
class InCommandPort : public BufferedPort<Bottle> {
    public:
        void setInCvPortPtr(BufferedPort<Bottle> *inCvPortPtr) {
            this->inCvPortPtr = inCvPortPtr;
        }

        void setIPositionControl(yarp::dev::IPositionControl *iPositionControl) {
            this->iPositionControl = iPositionControl;
        }
        void setCartesianPortPtr(yarp::os::RpcClient *cartesianPortPtr) {
            this->cartesianPortPtr = cartesianPortPtr;
        }

    protected:
        /** Callback on incoming Bottle. **/
        virtual void onRead(Bottle& b);

        BufferedPort<Bottle>* inCvPortPtr;

        yarp::os::RpcClient *cartesianPortPtr;
        yarp::dev::IPositionControl *iPositionControl;

        void movjWithWait(KDL::Frame& frame);
        void jointsWithWait(double* targets);
        void stat();
        void gripper(const int& value);
};

}  // namespace teo

#endif  // __IN_SR_PORT_HPP__
