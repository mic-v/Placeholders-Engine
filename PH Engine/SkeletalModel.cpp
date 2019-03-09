#include "SkeletalModel.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
// Based on: http://ogldev.atspace.co.uk/www/tutorial38/tutorial38.html //
//////////////////////////////////////////////////////////////////////////

namespace SA
{
	SkeletalModel::SkeletalModel() 
		: m_AnimationTime(0.0f), m_AnimationTime2(0.0f)
	{
		Clear();
	}





	SkeletalModel::~SkeletalModel()
	{
		Clear();
	}





	void SkeletalModel::setAnimation2(sAnimation * temp)
	{
		if (!m_isBlending && temp->ID != m_Animation.ID) {
			m_Animation2 = *temp;
			m_GlobalInverseTransform2 = temp->GlobalInverseTransform;
			m_isBlending = true;
		}
		//else we can add animations to queues and play them later
		
	}

	void SkeletalModel::startBlend(float Dt)
	{

		if (m_isBlending && m_Animation2.ID != m_Animation.ID) {
			if (m_SlerpTime < 1.0f) {
				m_SlerpTime += 3.5 * Dt;
			}
			else if(m_Animation2.Loopable){
				m_isBlending = false;
				m_SlerpTime = 0.0f;
				m_Animation = m_Animation2;
				m_AnimationTime = m_AnimationTime2;
				m_AnimationTime2 = 0.0f;
			}
			else if (m_Animation2.Played) {
				m_SlerpTime = 0.0f;
				std::swap(m_Animation, m_Animation2);
				m_Animation2 = m_Transition;
				m_AnimationTime = m_AnimationTime2;
				m_AnimationTime2 = 0.0f;
			}
		}
		else {
			m_isBlending = false;
		}
	}

	

	void SkeletalModel::Clear()
	{
		for (unsigned int i = 0; i < m_Meshes.size(); ++i)
		{
			delete[] m_Meshes[i].pVertices;
			delete[] m_Meshes[i].pNormals;
			delete[] m_Meshes[i].pUVs;
			delete[] m_Meshes[i].pTransformedVertices;
			delete[] m_Meshes[i].pTransformedNormals;
			delete[] m_Meshes[i].pIndices;
		}
		m_Meshes.clear();

		for (unsigned int i = 0; i < m_Skeleton.Bones.size(); ++i)
		{
			delete[] m_Skeleton.Bones[i].pWeights;
			delete[] m_Skeleton.Bones[i].pChildren;
		}
		m_Skeleton.Bones.clear();

		m_Animation.NodeAnimations.clear();
		m_Animation.Duration = 0.0f;
		m_Animation.TicksPerSecond = 0.0f;

		m_GlobalInverseTransform = glm::mat4x4(1);
		m_AnimationTime = 0.0f;
	}

	void SkeletalModel::playAnimations(float Dt)
	{
		if (m_isBlending) {
			if (m_Animation2.Loopable) {
				m_AnimationTime2 = fmodf(m_AnimationTime2 + Dt * m_Animation2.TicksPerSecond, m_Animation2.Duration);
			}
			else {
				float temptime2 = m_AnimationTime2 + Dt * m_Animation2.TicksPerSecond;
				if (temptime2 - m_Animation2.Duration > 0) {
					m_AnimationTime2 = temptime2 - m_Animation2.Duration;
					m_Animation2.Played = true;
				}
				else {
					m_AnimationTime2 = temptime2;
				}
			}
		}

		if (!m_Animation.Played) {
			float temptime1 = m_AnimationTime + Dt * m_Animation.TicksPerSecond;
			if (temptime1 - m_Animation.Duration > 0) {
				m_AnimationTime = temptime1 - m_Animation.Duration;
			}
			else {
				m_AnimationTime = temptime1;
			}

		}
	}



	void SkeletalModel::Update(float a_Dt)
	{
		startBlend(a_Dt);
		
		playAnimations(a_Dt);

		
		ReadNodeHierarchy(m_AnimationTime, m_AnimationTime2, m_Animation, m_Skeleton, m_Skeleton.Bones[0], m_Skeleton.Bones[0].NodeTransform);

	}





	void SkeletalModel::ReadNodeHierarchy(float AnimationTime, float AnimationTime2, sAnimation& a_Animation, sSkeleton& a_Skeleton, sBone& a_Bone, const glm::mat4x4& ParentTransform)
	{
		std::string NodeName(a_Bone.Name);
		glm::mat4x4 NodeTransformation(a_Bone.NodeTransform);
		const sNodeAnimation* pNewNodeAnim = FindNodeAnim(a_Animation, NodeName);
		const sNodeAnimation* pNewNodeAnim2 = nullptr;
		
		if (m_isBlending) {

			pNewNodeAnim2 = FindNodeAnim(m_Animation2, NodeName);
		}


		if (pNewNodeAnim)
		{
			glm::vec3 Translation = NodeAnimation_FindInterpolatedPosition(*pNewNodeAnim, AnimationTime);
			glm::quat RotationQ = NodeAnimation_FindInterpolatedRotation(*pNewNodeAnim, AnimationTime);


			glm::mat4x4 RotationM2;
			glm::mat4x4 TranslationM2;


			if (m_isBlending) {
				glm::quat RotationQ2 = NodeAnimation_FindInterpolatedRotation(*pNewNodeAnim2, AnimationTime2);
				RotationM2 = glm::toMat4(glm::slerp(RotationQ, RotationQ2, m_SlerpTime));
				
				TranslationM2 = glm::translate(Translation);
				if (NodeName == "Hips") {
					glm::vec3 Translation2 = NodeAnimation_FindInterpolatedPosition(*pNewNodeAnim2, AnimationTime2);
					TranslationM2 = glm::translate(glm::lerp(Translation, Translation2, m_SlerpTime));
				}
				
				

			}
			else {
				RotationM2 = glm::toMat4(RotationQ);
				TranslationM2 = glm::translate(Translation);
			}


			// Combine the above transformations
			NodeTransformation = TranslationM2 * RotationM2;// *ScalingM2;
		}
		
		glm::mat4x4 GlobalTransformation = ParentTransform * NodeTransformation;

		unsigned int BoneIndex = Skeleton_FindBoneIndex(a_Skeleton, NodeName);

		if (BoneIndex != -1)
		{
			sBone* pBone = &a_Skeleton.Bones[BoneIndex];
			pBone->FinalTransformation = m_GlobalInverseTransform * GlobalTransformation * pBone->OffsetMatrix;
			
		}
		else {
			std::cout << NodeName << std::endl;
		}

		for (unsigned int i = 0; i < a_Bone.NumChildren; i++)
		{
			ReadNodeHierarchy(AnimationTime, AnimationTime2, a_Animation, a_Skeleton, a_Skeleton.Bones[a_Bone.pChildren[i]], GlobalTransformation);
		}
	}


	void SkeletalModel::loadHierarchy() {
		this->Initialize(this->GetSkeleton());
	}
	void SkeletalModel::sendToShader(Shader *temp) {
		for (int i = 0; i < this->GetSkeleton().Bones.size(); i++) {
			temp->sendUniformMat4("BoneTransforms[" + std::to_string(i) + "]", this->GetSkeleton().Bones[i].FinalTransformation);
		}
		
	}


	void SkeletalModel::Initialize(const sSkeleton& a_Skeleton)
	{
		for (unsigned int i = 0; i < m_Meshes.size(); ++i)
		{
			// Reset mesh vertices and normals
			sAnimatedMesh& AnimMesh = m_Meshes[i];
			memset(AnimMesh.pTransformedVertices, 0, AnimMesh.NumVertices* sizeof(glm::vec3));
			memset(AnimMesh.pTransformedNormals, 0, AnimMesh.NumVertices* sizeof(glm::vec3));


			//EACH OF THESE CORRESPONDS WITH THE CORRECT ID OF THE VERTICES
			std::vector<glm::vec4> tempbonesofvertdata(m_Meshes[i].NumVertices, glm::vec4(0.0f));
			std::vector<glm::vec4> tempweightdata(m_Meshes[i].NumVertices, glm::vec4(0.0f));
			
			

			int weights = 0;
			for (unsigned int i = 0; i < a_Skeleton.Bones.size(); ++i)
			{
				const sBone& Bone = a_Skeleton.Bones[i];
				
				glm::mat4x4 Transformation = Bone.FinalTransformation;

				glm::mat3x3 Rotation = glm::mat3x3(Transformation);


				for (unsigned int j = 0; j < Bone.NumWeights; ++j)
				{
					sWeight Weight = Bone.pWeights[j];

					if (tempbonesofvertdata[Weight.VertexID].x == 0.0f) {
						tempbonesofvertdata[Weight.VertexID].x = i;
						tempweightdata[Weight.VertexID].x = Weight.Weight;
					}
					else if (tempbonesofvertdata[Weight.VertexID].y == 0.0f) {
						tempbonesofvertdata[Weight.VertexID].y = i;
						tempweightdata[Weight.VertexID].y = Weight.Weight;
					}
					else if (tempbonesofvertdata[Weight.VertexID].z == 0.0f) {
						tempbonesofvertdata[Weight.VertexID].z = i;
						tempweightdata[Weight.VertexID].z = Weight.Weight;
					}
					else if (tempbonesofvertdata[Weight.VertexID].w == 0.0f) {
						tempbonesofvertdata[Weight.VertexID].w = i;
						tempweightdata[Weight.VertexID].w = Weight.Weight;
					}
				}
				
				
			}

			vertbonedata = tempbonesofvertdata;
			weightdata = tempweightdata;
			
		}

	
	}





	const sNodeAnimation* FindNodeAnim(const sAnimation& a_Animation, const std::string& a_NodeName)
	{
		for (unsigned int i = 0; i < a_Animation.NodeAnimations.size(); ++i)
		{
			const sNodeAnimation& NodeAnim = a_Animation.NodeAnimations[i];
			if (NodeAnim.Name == a_NodeName)
			{
				return &NodeAnim;
			}
		}

		return NULL;
	}





	glm::vec3 InterpolateValue(const glm::vec3& a_Start, const glm::vec3& a_End, float a_Factor)
	{
		return glm::lerp(a_Start, a_End, a_Factor);
	}





	glm::quat InterpolateValue(const glm::quat& a_Start, const glm::quat& a_End, float a_Factor)
	{
		return glm::slerp(a_Start, a_End, a_Factor);
	}





	unsigned int Skeleton_FindBoneIndex(const sSkeleton& a_Skeleton, const std::string& a_Name)
	{
		for (unsigned int i = 0; i < a_Skeleton.Bones.size(); ++i)
		{
			if (a_Skeleton.Bones[i].Name == a_Name)
				return i;
		}
		return -1;
	}





	sBone* Skeleton_FindBone(sSkeleton& a_Skeleton, const std::string& a_Name)
	{
		return &a_Skeleton.Bones[Skeleton_FindBoneIndex(a_Skeleton, a_Name)];
	}
}