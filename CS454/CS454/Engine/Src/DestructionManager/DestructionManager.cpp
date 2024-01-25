#include "../../Include/Util/DestructionManager.h"

void LatelyDestroyable::Delete(void)
{
	assert(!dying); dying = true; delete this;
}
void DestructionManager::Register(LatelyDestroyable* d) {
	assert(!d->IsAlive());
	dead.push_back(d);
}
void DestructionManager::Commit(void) {
	for (auto* d : dead)
		d->Delete();
	dead.clear();
}
