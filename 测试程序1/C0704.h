#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class C0704
{
public:
	static const char* str0704;
	static unsigned char* msg0704;
	static int msg0704len;

	static unsigned char* Str2Array(const char* str_)
	{
		int _len = strlen(str_);
		msg0704len = _len / 2;
		unsigned char* retbuf = new unsigned char[_len / 2];

		for (int i = 0, c = 0; i < _len; i += 2, c++)
		{
			retbuf[c] = 0;
			switch (str_[i])
			{
			case '0': retbuf[c] = 0; break;
			case '1':retbuf[c] = 1; break;
			case '2':retbuf[c] = 2; break;
			case '3':retbuf[c] = 3; break;
			case '4':retbuf[c] = 4; break;
			case '5':retbuf[c] = 5; break;
			case '6':retbuf[c] = 6; break;
			case '7':retbuf[c] = 7; break;
			case '8':retbuf[c] = 8; break;
			case '9':retbuf[c] = 9; break;
			case 'a':retbuf[c] = 10; break;
			case 'b':retbuf[c] = 11; break;
			case 'c':retbuf[c] = 12; break;
			case 'd':retbuf[c] = 13; break;
			case 'e':retbuf[c] = 14; break;
			case 'f':retbuf[c] = 15; break;
			case 'A':retbuf[c] = 10; break;
			case 'B':retbuf[c] = 11; break;
			case 'C':retbuf[c] = 12; break;
			case 'D':retbuf[c] = 13; break;
			case 'E':retbuf[c] = 14; break;
			case 'F':retbuf[c] = 15; break;
			default:
				return 0;
			}

			retbuf[c] = retbuf[c] << 4;
			switch (str_[i + 1])
			{
			case '0': retbuf[c] += 0; break;
			case '1':retbuf[c] += 1; break;
			case '2':retbuf[c] += 2; break;
			case '3':retbuf[c] += 3; break;
			case '4':retbuf[c] += 4; break;
			case '5':retbuf[c] += 5; break;
			case '6':retbuf[c] += 6; break;
			case '7':retbuf[c] += 7; break;
			case '8':retbuf[c] += 8; break;
			case '9':retbuf[c] += 9; break;
			case 'a':retbuf[c] += 10; break;
			case 'b':retbuf[c] += 11; break;
			case 'c':retbuf[c] += 12; break;
			case 'd':retbuf[c] += 13; break;
			case 'e':retbuf[c] += 14; break;
			case 'f':retbuf[c] += 15; break;
			case 'A':retbuf[c] += 10; break;
			case 'B':retbuf[c] += 11; break;
			case 'C':retbuf[c] += 12; break;
			case 'D':retbuf[c] += 13; break;
			case 'E':retbuf[c] += 14; break;
			case 'F':retbuf[c] += 15; break;
			default:
				return 0;
			}
		}
		return retbuf;
	}

	static const int send0704len = 1;
	static unsigned char* send0704[send0704len];
	static int Generate0704(unsigned char* clone_, int len_)
	{
		for (int i = 0; i < send0704len; i++)
		{
			unsigned char* _newmsg = new unsigned char[len_];
			memcpy(_newmsg, clone_, len_);
			int* pint = (int*)(_newmsg + 7);
			*pint = i;

			unsigned char _crc = 0;
			for (int c = 1; c < (len_ - 2); c++)
			{
				_crc = _crc ^ _newmsg[c];
			}
			_newmsg[len_ - 2] = _crc;

			send0704[i] = _newmsg;
		}
		return 0;
	}

	static int BCD2int(unsigned char c_)
	{
		int ret = 0;
		switch (c_ & 0x0F)
		{
		case 0:ret = 0; break;
		case 1:ret = 1; break;
		case 2:ret = 2; break;
		case 3:ret = 3; break;
		case 4:ret = 4; break;

		case 5:ret = 5; break;
		case 6:ret = 6; break;
		case 7:ret = 7; break;
		case 8:ret = 8; break;
		case 9:ret = 9; break;
		default:break;
		}

		switch (c_ & 0xF0)
		{
		case 0x00:ret += 0; break;
		case 0x10:ret += 10; break;
		case 0x20:ret += 20; break;
		case 0x30:ret += 30; break;
		case 0x40:ret += 40; break;

		case 0x50:ret += 50; break;
		case 0x60:ret += 60; break;
		case 0x70:ret += 70; break;
		case 0x80:ret += 80; break;
		case 0x90:ret += 90; break;
		default:break;
		}
		return ret;
	}

	static unsigned char Int2BCD(int num_)
	{
		unsigned char ret = 0;
		switch (num_ % 10)
		{
		case 0:ret = 0; break;
		case 1:ret = 1; break;
		case 2:ret = 2; break;
		case 3:ret = 3; break;
		case 4:ret = 4; break;

		case 5:ret = 5; break;
		case 6:ret = 6; break;
		case 7:ret = 7; break;
		case 8:ret = 8; break;
		case 9:ret = 9; break;
		default:break;
		}

		switch (num_ / 10)
		{
		case 0:ret += 0; break;
		case 1:ret += 0x10; break;
		case 2:ret += 0x20; break;
		case 3:ret += 0x30; break;
		case 4:ret += 0x40; break;

		case 5:ret += 0x50; break;
		case 6:ret += 0x60; break;
		case 7:ret += 0x70; break;
		case 8:ret += 0x80; break;
		case 9:ret += 0x90; break;
		default:break;
		}
		return ret;
	}

	static void ChangeTime()
	{
		for (int i = 0; i < send0704len; i++)
		{
			for (int c = 0; c < msg0704len; ++c)
			{
				if (send0704[i][c] == 0x20)
				{
					if (send0704[i][c + 1] == 0x05)
					{
						if (send0704[i][c + 2] == 0x07)
						{
							if ((BCD2int(send0704[i][c + 5]) + 20) >= 60)
							{
								send0704[i][c + 5] = Int2BCD((BCD2int(send0704[i][c + 5]) + 20) % 60);
								if ((BCD2int(send0704[i][c + 4]) + 1) >= 60)
								{
									send0704[i][c + 4] = 0;
									if (send0704[i][c + 3] >= 24)
									{
										send0704[i][c + 3] = 0;
									}
									else
									{
										send0704[i][c + 3] = Int2BCD(BCD2int(send0704[i][c + 3]) + 1);
									}
								}
								else
								{
									send0704[i][c + 4] = Int2BCD(BCD2int(send0704[i][c + 4]) + 1);
								}
							}
							else
							{
								send0704[i][c + 5] = Int2BCD((BCD2int(send0704[i][c + 5]) + 20) % 60);
							}
						}
					}
				}
			}
		}
	}

};

