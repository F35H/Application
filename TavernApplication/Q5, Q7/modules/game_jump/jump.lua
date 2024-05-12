JumpWindow = {}

jumpWindow = nil

--I'm going to be honest, I don't know how to do this.
--The wiki is clearly right here: https://github.com/edubart/otclient/wiki/Module-Tutorial#reloading-your-module
--I genuinely am unsure what to do here. This doesn't show up in the OTClient at all despite the fact it says it should.

function init()
  connect(g_game, { onOpenSpellWindow = JumpWindow.create, onGameEnd = JumpWindow.destroy })
end

function terminate()
  disconnect(g_game, { onOpenSpellWindow = JumpWindow.create, onGameEnd = JumpWindow.destroy })
  JumpWindow.destroy()
  JumpWindow = nil
end

function JumpWindow.create(spellList)
  jumpWindow = g_ui.displayUI('jump.otui')
end

function JumpWindow.destroy()
  if jumpWindow then
    jumpWindow:destroy()
    jumpWindow = nil
  end
end

