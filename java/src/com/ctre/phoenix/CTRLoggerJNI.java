package com.ctre.phoenix;
import com.ctre.phoenix.MotorControl.CTREJNIWrapper;

public class CTRLoggerJNI extends CTREJNIWrapper
{
	public static native void JNI_Logger_Close();
	public static native int JNI_Logger_Log(int code, String origin, String stackTrace);
	public static native void JNI_Logger_Open(int language);
	public static native String JNI_Logger_GetShort(int code);
	public static native String JNI_Logger_GetLong(int code);
}

