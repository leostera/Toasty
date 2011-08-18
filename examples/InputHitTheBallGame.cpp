#include <Toasty.h>

class Ball : public ITyActor
{
public:
	Ball() : ITyActor(0)
	{
		this->AddState(new TySprite("sprites.group","Pollo"), TOASTY_ACTOR_STATE_WALKING);
		this->AddState(new TySprite("sprites.group","PolloGolpe"), TOASTY_ACTOR_STATE_USER0);
		this->SetCurrentState(TOASTY_ACTOR_STATE_WALKING);
	}
};

int maint (int argc, char** argv)
{
	TySystemInit(TOASTY_INIT_2D|TOASTY_INIT_INPUT|TOASTY_INIT_CLOCK|TOASTY_INIT_SCENE_MGR);

	TyScene* escena = TyGetSceneMgr()->AddScene(();
	escena->AddActor( new Ball() );

	TyGetSceneMgr()->SetCurrentScene(escena);
	
	while(TyGetSceneMgr()->Play());

	TySystemTerminate(TOASTY_INIT_2D|TOASTY_INIT_INPUT|TOASTY_INIT_CLOCK|TOASTY_INIT_SCENE_MGR);
}
