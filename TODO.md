## Chipmunk functions missing bindings on _ChipmunkServer_

The following functions are missing bindings on `ChipmunkServer` and therefore cannot be invoked from GDScript. They can, of course, still be called from C++ code.

### On cpSpace.h

- cpSpaceAlloc
- cpSpaceInit
- cpSpaceDestroy
- cpSpaceGetUserData
- cpSpaceSetUserData
- cpSpaceGetStaticBody
- cpSpaceAddDefaultCollisionHandler
- cpSpaceAddCollisionHandler
- cpSpaceAddWildcardHandler
- cpSpaceAddPostStepCallback
- cpSpaceSegmentQuery
- cpSpaceSegmentQueryFirst
- cpSpaceBBQuery
- cpSpaceShapeQuery
- cpSpaceEachBody
- cpSpaceEachShape
- cpSpaceEachConstraint
- cpSpaceDebugDraw

### On cpBody.h

- cpBodyAlloc
- cpBodyInit
- cpBodyDestroy
- cpBodyGetUserData
- cpBodySetUserData
- cpBodySetVelocityUpdateFunc
- cpBodySetPositionUpdateFunc
- cpBodyEachShape
- cpBodyEachConstraint
- cpBodyEachArbiter

### On cpShape.h

- cpShapeDestroy
- cpShapePointQuery
- cpShapeSegmentQuery
- cpShapesCollide
- cpShapeGetUserData
- cpShapeSetUserData
- cpCircleShapeAlloc
- cpCircleShapeInit
- cpSegmentShapeAlloc
- cpSegmentShapeInit

### On cpPolyShape.h

- cpPolyShapeAlloc
- cpPolyShapeInit
- cpPolyShapeInitRaw
- cpBoxShapeInit
- cpBoxShapeInit2

### On cpConstraint.h

- cpConstraintDestroy
- cpConstraintGetPreSolveFunc
- cpConstraintSetPreSolveFunc
- cpConstraintGetPostSolveFunc
- cpConstraintSetPostSolveFunc
- cpConstraintGetUserData
- cpConstraintSetUserData

### On cpPinJoint.h

- cpPinJointAlloc
- cpPinJointInit
