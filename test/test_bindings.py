import os
import sys

test_directory = os.path.dirname(os.path.realpath(__file__))
sys.path.insert(0, os.path.join(test_directory, '..', 'build'))

import dtk3

def test_factory():
    print('Testing ModelComponentFactory...')
    mc = dtk3.ModelComponent("SimpleBoostDecayComponent", dict(boostAmount=2.7, decayRate=0.2))
    mc.Notify("Boost")
    print('value=%0.2f after Boost(2.7)' % mc.currentValue)
    mc.Update(dt=5)
    print('value=%0.2f after Decay(dt=5, decayRate=0.2)' % mc.currentValue)

def test_constructor():
    print('Testing SimpleBoostDecayComponent constructor...')
    mc = dtk3.SimpleBoostDecayComponent()
    mc.Configure(dict(boostAmount=2, decayRate=0))
    mc.Notify("Boost")
    print('value=%0.2f after Boost(2)' % mc.currentValue)

if __name__ == '__main__':
    test_factory()
    test_constructor()
