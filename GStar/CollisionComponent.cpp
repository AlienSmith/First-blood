#include "CollisionComponent.h"
#include "TransformComponent.h"
GStar::CollisionComponent::CollisionComponent(TransformComponent * trans):my_transform(trans){}

GStar::CollisionComponent::CollisionComponent(TransformComponent * trans, const Vector3 & offset):my_transform(trans),offsets(offset){}
