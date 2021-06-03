#include "../includes/sceneCore.h"

void Scene::addGameObject(ObjectInfo info)
{
	//put a new object in the scene
	info.program = createShader(info.shaderDirs);

	createMesh(info);

	applyStaticRotation(info);

	convertMeshToArray(info.objectMesh, info.convertedMesh);

	info.physicsObject.position = info.position;

	sceneObjects.insert(std::pair<std::string, ObjectInfo>(info.name, info));
}

void Scene::setStepFunction(std::string objName, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)> func)
{
	//set the function that is suppost to run at step (every render cycle)
	std::map<std::string, ObjectInfo>::iterator it;

	it = sceneObjects.find(objName);
	if (it == sceneObjects.end())
		throw "The object you are tring to asign a function to doesn't exist";

	stepFunctions.insert(std::pair<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>(objName, func));
}

void Scene::setCreateFunction(std::string objName, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)> func)
{
	//set the create function (runs before the render cycle)
	std::map<std::string, ObjectInfo>::iterator it;

	it = sceneObjects.find(objName);
	if(it == sceneObjects.end())
		throw "The object you are tring to asign a function to doesn't exist";

	createFunctions.insert(std::pair<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>(objName, func));
}

void Scene::callStepFunction(std::string objName)
{
	Viewport* vp = new Viewport(sceneObjects[objName].convertedMesh, sceneObjects[objName].drawType);

	vp->bindBuffer(sceneObjects[objName].program, sceneObjects[objName].depthTest, sceneObjects[objName].buffer);

	glUseProgram(sceneObjects[objName].program);

	//call the before asigned step function
	std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>::const_iterator el;
	el = stepFunctions.find(objName);
	if (el == stepFunctions.end())
		return;

	el->second(sceneObjects, objName, sceneCamera);
	
	vecs::vec3 vec = { sceneObjects[objName].physicsObject.position.x, 
					   sceneObjects[objName].physicsObject.position.y, 
					   sceneObjects[objName].physicsObject.position.z };

	vecs::vec3 camPos = {
		sceneCamera.pos.x, 
		sceneCamera.pos.y, 
		sceneCamera.pos.z
	};
	
	sceneObjects[objName].tex.bind();

	vecs::mat4 yawMat = vc::rotY(-sceneCamera.yaw);
	vecs::mat4 pitchMat = vc::rotX(-sceneCamera.pitch);
	vecs::mat4 rollMat = vc::rotZ(-sceneCamera.roll);

	//get uniform locations to bind the predefined uniforms
	int uTexture = glGetUniformLocation(sceneObjects[objName].program, "uTexture");
	int uWorld = glGetUniformLocation(sceneObjects[objName].program, "uWorld");
	int uWorldInvTran = glGetUniformLocation(sceneObjects[objName].program, "uWorldInvTran");
	int uViewMat = glGetUniformLocation(sceneObjects[objName].program, "uViewMat");
	int uCameraPos = glGetUniformLocation(sceneObjects[objName].program, "uCameraPos");
	int uObjPos = glGetUniformLocation(sceneObjects[objName].program, "uObjPos");
	int uYaw = glGetUniformLocation(sceneObjects[objName].program, "uYaw");
	int uYawMat = glGetUniformLocation(sceneObjects[objName].program, "uYawMat");
	int uPitch = glGetUniformLocation(sceneObjects[objName].program, "uPitch");
	int uPitchMat = glGetUniformLocation(sceneObjects[objName].program, "uPitchMat");
	int uRoll = glGetUniformLocation(sceneObjects[objName].program, "uRoll");
	int uRollMat = glGetUniformLocation(sceneObjects[objName].program, "uRollMat");

	glUniform1i(uTexture, 0);
	glUniformMatrix4fv(uWorld, 1, GL_FALSE, &worldMat.r[0][0]);
	glUniformMatrix4fv(uWorldInvTran, 1, GL_FALSE, &transposedWorldMat.r[0][0]);
	glUniformMatrix4fv(uViewMat, 1, GL_FALSE, &viewMat.r[0][0]);
	glUniform3f(uCameraPos, camPos.x, camPos.y, camPos.z);
	glUniform3f(uObjPos, vec.x, vec.y, vec.z);
	glUniform1f(uYaw, sceneCamera.yaw);
	glUniform1f(uPitch, sceneCamera.pitch);
	glUniform1f(uRoll, sceneCamera.roll);
	glUniformMatrix4fv(uYawMat, 1, GL_FALSE, &yawMat.r[0][0]);
	glUniformMatrix4fv(uPitchMat, 1, GL_FALSE, &pitchMat.r[0][0]);
	glUniformMatrix4fv(uRollMat, 1, GL_FALSE, &rollMat.r[0][0]);

	glDrawArrays(GL_TRIANGLES, 0, sceneObjects[objName].convertedMesh.size() / 6);

	glDeleteBuffers(1, &sceneObjects[objName].buffer);

	sceneObjects[objName].tex.unbind();

	delete vp;
}

void Scene::callCreateFunction(std::string objName)
{
	//call the before asigned create function
	std::map<std::string, std::function<void(std::map<std::string, ObjectInfo>&, std::string, Camera&)>>::const_iterator el;
	el = createFunctions.find(objName);
	if (el == createFunctions.end())
		return;

	if (sceneObjects[objName].enablePhysics)
		phyWorld.addObject(&sceneObjects[objName].physicsObject);

	el->second(sceneObjects, objName, sceneCamera);
}

void Scene::addCameraProjMat(float width, float height, float fFar, float fNear, float fov)
{
	//add the projection matrix to the scene camera
	const float fovRad = 1 / tanf(fov * 0.5f / 180.0f * (float)PI);

	const float aspectRatio = height / width;

	sceneCamera.projMat = {
		aspectRatio * fovRad, 0.0f, 0.0f, 0.0f,
		0.0f, fovRad, 0.0f, 0.0f,
		0.0f, 0.0f, fFar / (fFar - fNear), 1.0f,
		0.0f, 0.0f, (-fFar * fNear) / (fFar - fNear), 0.0f
	};
}

void Scene::calculateViewMat(Camera& cam)
{
	//add the new look directions to the camera position
	cam.pos = cam.pos + (cam.lookDir * cam.forward) + (cam.lookDirSqued * cam.sideways) + (cam.lookDirSquedUp * cam.vertical);

	//targets for all 3 axis
	vecs::vec3 vTargetF = { 0.0f, 0.0f, 1.0f };

	//create camera rotation matrix for yaw
	vecs::mat4 mCameraRot = vc::rotY(cam.yaw);

	//add up the new look directions with the new camera rotation
	cam.lookDir = vc::customVecMultiply(mCameraRot, vTargetF);
	cam.lookDirSqued = vc::customVecMultiply(mCameraRot, { 1.0f, 0.0f, 0.0f });
	cam.lookDirSquedUp = vc::customVecMultiply(mCameraRot, { 0.0f, 1.0f, 0.0f });

	//asign new target
	vTargetF = cam.pos + cam.lookDir;

	viewMat =  createViewMatrix(cam.projMat, cam.pos, vTargetF, cam.up, cam.pitch, 0.0f, 0.0f);
}

void Scene::calculateWorldMat()
{
	//calculates the world and the inverted transposed world mat 
	worldMat = createWorldMatrix(dynamicSceneRotation, { 0.0f, 0.0f, 0.0f }, 1.0f);
	transposedWorldMat = vc::transposeMat(vc::quickInverse(worldMat));
}

void Scene::applyStaticSceneRotation()
{
	for (auto& kv : sceneObjects)
	{
		vecs::mesh endWorld;

		for (const auto& tri : kv.second.objectMesh.tris)
		{
			vecs::vec3 t0 = vc::customVecMultiply(createWorldMatrix(staticSceneRotation, kv.second.position, 1.0f), tri.p[0]);
			vecs::vec3 t1 = vc::customVecMultiply(createWorldMatrix(staticSceneRotation, kv.second.position, 1.0f), tri.p[1]);
			vecs::vec3 t2 = vc::customVecMultiply(createWorldMatrix(staticSceneRotation, kv.second.position, 1.0f), tri.p[2]);

			endWorld.tris.push_back({ { t0, t1, t2 }, { tri.texUv[0], tri.texUv[1], tri.texUv[2] }, tri.color, tri.normal});
		}

		kv.second.objectMesh = endWorld;
	}
}

void Scene::sceneStep(float deltaTime)
{
	//things that need to be called at step but not multiple times
	calculateViewMat(sceneCamera);
	calculateWorldMat();

	phyWorld.step(deltaTime);
}

void Scene::sceneCreate()
{
	//things that run before the render cycle and don't need to be done repetativly
	calculateViewMat(sceneCamera);
	calculateWorldMat();
}

std::vector<std::string> Scene::objectNames()
{
	std::vector<std::string> objName;

	for (const auto& sceneObj : sceneObjects)
	{
		objName.push_back(sceneObj.second.name);
	}

	return objName;
}