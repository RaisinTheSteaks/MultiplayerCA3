#include <SDL_events.h>

class Engine
{
public:

	virtual ~Engine();
	static std::unique_ptr< Engine >	sInstance;

	virtual int		Run();
	void			SetShouldKeepRunning( bool inShouldKeepRunning ) { mShouldKeepRunning = inShouldKeepRunning; }
	virtual void	HandleEvent(sf::Event &p_event);
	virtual bool	PullEvent(sf::Event &p_event);

protected:

	Engine();

	virtual void	DoFrame();

private:


			
			int		DoRunLoop();

			bool	mShouldKeepRunning;



};