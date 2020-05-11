class Client : public Engine
{
public:

	static bool StaticInit( );

protected:

	Client();

	virtual void	DoFrame() override;
	virtual void	HandleEvent( sf::Event &p_event ) override;
	virtual bool	PullEvent(sf::Event &p_event) override;

private:



};