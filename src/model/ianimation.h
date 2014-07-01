/*This file is part of QEditor.

QEditor is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

QEditor is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with QEditor.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef IANIMATION_H
#define IANIMATION_H

#include <QtWidgets>

#include "ibone.h"

class IAnimation
{
public:
    IAnimation(QString animation_name, float animation_duration, int animation_id);
    ~IAnimation();

    void addBonePosition(int bone_id, float time, QVector3D   position);
    void addBoneScaling(int bone_id,  float time, QVector3D   scaling);
    void addBoneRotation(int bone_id, float time, QQuaternion rotation);

    void registerBone(int boneId);

    bool isRegistered(int boneId);

    void setBoneCount(int count);

    int getId();
    int getBoneCount();

    float getDuration();

    QString getName();

    QVector<QMatrix4x4> getTransforms(float time_stamp, QMap<int, QPair<float, int>>* position_state, QMap<int, QPair<float, int>>* scaling_state, QMap<int, QPair<float, int>>* rotation_state);

    QMap<int, QVector<QPair<float, QVector3D>>>*   getPositions();
    QMap<int, QVector<QPair<float, QVector3D>>>*   getScalings();
    QMap<int, QVector<QPair<float, QQuaternion>>>* getRotations();

private:
    float duration;

    QString name;

    int id;

    unsigned int bone_count;

    QMap<int, QVector<QPair<float, QVector3D>>>   positions;
    QMap<int, QVector<QPair<float, QVector3D>>>   scalings;
    QMap<int, QVector<QPair<float, QQuaternion>>> rotations;

    QVector<int> boneRegister;
};

class IAnimations
{
public:
    IAnimations();
    ~IAnimations();

    void add(IAnimation* _animation);

    void setBones(IBones* Bones);

    IAnimation* get(int id);
    IBones*     getBones();

    QVector<QString> getAnimationNames();
    QVector<int>     getAnimationsIds();

    int getAnimationCount();

private:
    IBones* Bones;

    QMap<int, IAnimation*> animations;
};

class IAnimationState
{
public:
    IAnimationState(IAnimations* anims);
    ~IAnimationState();

    void update(float frame_time);

    void setAnimation(int id, float animationTime = 0.0f);

    int   getAnimation();
    float getAnimationTime();

    QVector<QMatrix4x4> getTransforms();

    IAnimations* getAnimations();

private:
    IAnimations* animations;

    int current_animation;

    float animation_time;

    QMap<int, QPair<float, int>> position_state;
    QMap<int, QPair<float, int>> rotation_state;
    QMap<int, QPair<float, int>> scaling_state;

    QMap<int, QMatrix4x4> transforms;
};

#endif // IANIMATION_H