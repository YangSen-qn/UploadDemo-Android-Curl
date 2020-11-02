package com.example.uploaddemo_android;

import android.util.Log;

import org.junit.Test;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

import static org.junit.Assert.*;

/**
 * Example local unit test, which will execute on the development machine (host).
 *
 * @see <a href="http://d.android.com/tools/testing">Testing documentation</a>
 */
public class ExampleUnitTest {
    @Test
    public void addition_isCorrect() {
        assertEquals(4, 2 + 2);
    }

    @Test
    public void testA() {

        B b = new B() {
            @Override
            public void action() {
                Log.d("=== TestA", "b action");
            }
        };

        try {
            String ActionClassString = Action.class.toString();
            Class<?> ActionClass = Class.forName("com.example.uploaddemo_android.ExampleUnitTest$Action");
            IAction action = (IAction) ActionClass.newInstance();
            action.action(b);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    interface IAction {
        void action(B b);
    }
    interface B {
        void action();
    }

    static class Action implements IAction {

        @Override
        public void action(B b){
            if (b != null){
                b.action();
            }
        }
    }
}