#include "common/AnimationClip.h"

namespace te
{
    bool SkeletonRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;

        // Make sure header is available
        if (size < 8) return false; //("Invalid skeleton resource");
        
        char *data_ptr = (char *)data;

        // Check header and version
        char id[4];
        memcpy(&id, data_ptr, 4); data_ptr += 4;
        if (id[0] != 'H' || id[1] != '3' || id[2] != 'D' || id[3] != 'A')
            return false; //("Invalid animation resource");

        int version;
        memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        if (version != 2 && version != 3)
            return false; //("Unsupported version of animation resource");

        // Load skeleton data
        int entity_num;
        memcpy(&entity_num, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        _entities.resize(entity_num);

        for (int i = 0; i < entity_num; ++i)
        {
            JointEntity& entity = _entities[i];

            char name[256];
            int parent_idx;
            memcpy(name, data_ptr, 256); data_ptr += 256;
            entity.name = name;

            memcpy(&parent_idx, data_ptr, sizeof(int)); data_ptr += sizeof(int);
            entity.parent_idx = parent_idx;
        }

        return true;
    }

    void SkeletonRes::release()
    {}

    void SkeletonRes::buildSkeleton(Skeleton* skeleton)
    {
        int entity_num = _entities.size();
        skeleton->resize(entity_num);

        for (int i = 0; i < entity_num; ++i)
        {
            SkeletonJoint& joint = skeleton->getJoint(i);
            joint.name = _entities[i].name;
            joint.parent_idx = _entities[i].parent_idx;
            joint.inv_binding = _entities[i].inv_binding;
        }
    }

    // now using horde3d animation format
    bool AnimClipRes::load(const char *data, int size)
    {
        if (!Resource::load(data, size)) return false;

        // Make sure header is available
        if (size < 8) return false; //("Invalid animation resource");

        char *data_ptr = (char *)data;

        // Check header and version
        char id[4];
        memcpy(&id, data_ptr, 4); data_ptr += 4;
        if (id[0] != 'H' || id[1] != '3' || id[2] != 'D' || id[3] != 'A')
            return false; //("Invalid animation resource");

        int version;
        memcpy(&version, data_ptr, sizeof(int)); data_ptr += sizeof(int);
        if (version != 2 && version != 3)
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

        return true;
    }

    void AnimClipRes::release()
    {

    }

    void AnimClipRes::buildAnimClip(AnimationClip* anim_clip)
    {
        anim_clip->setFrameNum(_frame_num);
        for (int i = 0; i < _frame_num; ++i)
        {
            AnimationPoses& poses = anim_clip->getAnimPose(i);
            for (int j = 0, j_end = _entities.size(); j < j_end; ++ j)
            {
                poses[j].rotation = _entities[j].frames[i].rotation;
                poses[j].translation = _entities[j].frames[i].translation;
                poses[j].scale = _entities[j].frames[i].scale;
            }
        }
    }

    void Skeleton::resize(int size)
    {
        _joints.resize(size);
    }

    AnimationClip::AnimationClip(const AnimationClip& anim_clip, const CopyOperator& copyop)
    {

    }

    void AnimationClip::setFrameNum(int num)
    {
        _key_frames.resize(num);
    }
}
