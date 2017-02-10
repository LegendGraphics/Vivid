#include "common/AnimationClip.h"

namespace te
{
    bool SkeletonRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;
        
        char *data_ptr = (char *)data;

        // Check header and version
        char id[3];
        memcpy(&id, data_ptr, 3); data_ptr += 3;
        if (id[0] != 'T' || id[1] != 'E' || id[2] != 'S')
            return false; //("Invalid skeleton resource");

        int version;
        memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        if (version != 1)
            return false; //("Unsupported version of skeleton resource");

        // Load skeleton data
        int entity_num;
        memcpy(&entity_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        _entities.resize(entity_num);

        for (int i = 0; i < entity_num; ++i)
        {
            JointEntity& entity = _entities[i];

            char name[256];
            int parent_idx;
            float pose_values[16];
            Matrix inv_binding;
            memcpy(name, data_ptr, 256); data_ptr += 256;
            entity.name = name;

            memcpy(&parent_idx, data_ptr, sizeof(int)); data_ptr += sizeof(int);
            entity.parent_idx = parent_idx;

            for (int k = 0; k < 16; ++ k) memcpy(&pose_values[k], data_ptr, sizeof(float)); data_ptr += sizeof(float);
            entity.inv_binding.set(pose_values[0], pose_values[1], pose_values[2],pose_values[3],
                                   pose_values[4], pose_values[5], pose_values[6],pose_values[7],
                                   pose_values[8], pose_values[9], pose_values[10],pose_values[11],
                                   pose_values[12], pose_values[13], pose_values[14],pose_values[15]);
        }

        setResourceHandle();

        return true;
    }

    void SkeletonRes::release()
    {}

    // now using horde3d animation format
    bool AnimClipRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;

        char *data_ptr = (char *)data;

        // Check header and version
        char id[3];
        memcpy(&id, data_ptr, 3); data_ptr += 3;
        if (id[0] != 'T' || id[1] != 'E' || id[2] != 'A')
            return false; //("Invalid animation resource");

        int version;
        memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        if (version != 1)
            return false; //("Unsupported version of animation resource");

        // Load animation data
        int entity_num;
        memcpy(&entity_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        memcpy(&_frame_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);

        _entities.resize(entity_num);

        for (int i = 0; i < entity_num; ++i)
        {
            char name[256], compressed = 0;
            AnimResEntity& entity = _entities[i];

            memcpy(name, data_ptr, 256); data_ptr += 256;
            entity.name = name;

            // Animation compression
            if (version == 3)
            {
                memcpy(&compressed, data_ptr, sizeof(char)); data_ptr += sizeof(char);
            }

            entity.frames.resize(compressed ? 1 : _frame_num);
            for (int j = 0; j < (compressed ? 1 : _frame_num); ++j)
            {
                Frame &frame = entity.frames[j];

                memcpy(&frame.rotation.v.x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.rotation.v.y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.rotation.v.z, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.rotation.w, data_ptr, sizeof(float)); data_ptr += sizeof(float);

                memcpy(&frame.translation.x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.translation.y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.translation.z, data_ptr, sizeof(float)); data_ptr += sizeof(float);

                memcpy(&frame.scale.x, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.scale.y, data_ptr, sizeof(float)); data_ptr += sizeof(float);
                memcpy(&frame.scale.z, data_ptr, sizeof(float)); data_ptr += sizeof(float);

                //// Prebake transformation matrix for fast animation path
                //frame.baked_mat.scale(frame.scale.x, frame.scale.y, frame.scale.z);
                //frame.baked_mat = Matrix4f(frame.rotation) * frame.baked_mat;
                //frame.baked_mat.translate(frame.translation.x, frame.translation.y, frame.translation.z);
            }
        }

        setResourceHandle();

        return true;
    }

    void AnimClipRes::release()
    {

    }

    void AnimClipRes::initAnimClip(AnimationClip* anim_clip)
    {
        anim_clip->setFrameNum(_frame_num);
        for (int i = 0; i < _frame_num; ++i)
        {
            AnimationPoses& poses = anim_clip->getAnimPoses(i);
            for (int j = 0, j_end = _entities.size(); j < j_end; ++ j)
            {
                poses[j].rotation = _entities[j].frames[i].rotation;
                poses[j].translation = _entities[j].frames[i].translation;
                poses[j].scale = _entities[j].frames[i].scale;
            }
        }
    }

    void Skeleton::init(SkeletonRes* res)
    {
        int entity_num = res._entities.size();
        _joints.resize(entity_num);

        for (int i = 0; i < entity_num; ++i)
        {
            _joints[i].name = res._entities[i].name;
            _joints[i].parent_idx = res._entities[i].parent_idx;
            _joints[i].inv_binding = res._entities[i].inv_binding;
        }
    }

    void Skeleton::resize(int size)
    {
        _joints.resize(size);
    }

    SkeletonJoint& Skeleton::getJoint(int index)
    {
        assert(index < _joints.size());
        return _joints[index];
    }

    SkeletonJoint& Skeleton::getParentJoint(int index)
    {
        int pid = _joints[index].parent_idx;
        assert(pid != -1);
        return getJoint(pid);
    }

    AnimationClip::AnimationClip(const AnimationClip& anim_clip, const CopyOperator& copyop)
    {

    }

    void AnimationClip::init(AnimClipRes* res)
    {
        res->initAnimClip(this);
    }

    void AnimationClip::setFrameNum(int num)
    {
        _key_frames.resize(num);
    }
}
