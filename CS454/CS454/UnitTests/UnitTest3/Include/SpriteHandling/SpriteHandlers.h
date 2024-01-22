#include "../../../../Engine/Include/ZeldaApp.h"
#include "../../../../Engine/Include/Grid/Grid.h"
#include "../../../../Engine/Include/TileLayer.h"
#include "../../../../Engine/Include/Util/Print.h"
#include "../../../../Engine/Include/Grid/GridMotion.h"
#include "../../../../Engine/Include/Grid/GridCompute.h"
#include "../../../../Engine/Include/KeyFrameAnimation/AnimationFilmHolder.h"
#include "../../../../Engine/Include/Sprites/SpriteManager.h"

#include "../../../../Engine/Include/Sprites/SpriteHelpers.h"
#include "../../../../Engine/Include/Animators/AnimatorManager.h"
#include "../../../../Engine/Include/Animators/FrameRangeAnimator.h"
#include "../../../../Engine/Include/Animators/MovingAnimator.h"
#include "../../../../Engine/Include/Util/SystemClock.h"
#include "../../../../Engine/Include/Sprites/CollisionChecker.h"

void init_sprites(TileLayer *layer);
