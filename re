Project title : TP_test
Project path  : /home/sayantan/tp_test/TP_test/

Frame function: pthread_mutex_lock
Frame address : 0xbffff6c0
--------------------------------------------------------------------------------
0x283f10	push   ebp
0x283f11	mov    ebp,esp
0x283f13	sub    esp,0x24
0x283f16	mov    DWORD PTR [ebp-0x8],esi
0x283f19	mov    esi,DWORD PTR [ebp+0x8]
0x283f1c	mov    DWORD PTR [ebp-0xc],ebx
0x283f1f	mov    DWORD PTR [ebp-0x4],edi
0x283f22	call   0x280340 <__i686.get_pc_thunk.bx>
0x283f27	add    ebx,0xe0cd
0x283f2d	mov    edi,DWORD PTR [esi+0xc]
0x283f30	mov    ecx,edi
0x283f32	mov    eax,edi
0x283f34	and    ecx,0x7f
0x283f37	and    eax,0x7c
0x283f3a	jne    0x283f81 <pthread_mutex_lock+113>
0x283f3c	mov    edx,DWORD PTR gs:0x68
0x283f43	test   ecx,ecx
0x283f45	mov    DWORD PTR [ebp-0x10],edx
0x283f48	jne    0x283fbe <pthread_mutex_lock+174>
0x283f4a	and    edi,0x80
0x283f50	mov    ecx,0x1
0x283f55	xor    eax,eax
0x283f57	lock cmpxchg DWORD PTR [esi],ecx
0x283f5b	jne    0x284132 <_L_lock_748>
0x283f61	mov    eax,DWORD PTR [esi+0x8]
0x283f64	test   eax,eax
0x283f66	jne    0x283f94 <pthread_mutex_lock+132>
0x283f68	mov    eax,DWORD PTR [ebp-0x10]
0x283f6b	add    DWORD PTR [esi+0x10],0x1
0x283f6f	mov    DWORD PTR [esi+0x8],eax
0x283f72	xor    eax,eax
0x283f74	mov    ebx,DWORD PTR [ebp-0xc]
0x283f77	mov    esi,DWORD PTR [ebp-0x8]
0x283f7a	mov    edi,DWORD PTR [ebp-0x4]
0x283f7d	mov    esp,ebp
0x283f7f	pop    ebp
0x283f80	ret
0x283f81	mov    ebx,DWORD PTR [ebp-0xc]
0x283f84	mov    eax,esi
0x283f86	mov    edi,DWORD PTR [ebp-0x4]
0x283f89	mov    esi,DWORD PTR [ebp-0x8]
0x283f8c	mov    esp,ebp
0x283f8e	pop    ebp
0x283f8f	jmp    0x2839b0 <__pthread_mutex_lock_full>
0x283f94	lea    eax,[ebx-0x5586]
0x283f9a	mov    DWORD PTR [esp+0xc],eax
0x283f9e	mov    DWORD PTR [esp+0x8],0x3e
0x283fa6	lea    eax,[ebx-0x4e6a]
0x283fac	mov    DWORD PTR [esp+0x4],eax
0x283fb0	lea    eax,[ebx-0x55a1]
0x283fb6	mov    DWORD PTR [esp],eax
0x283fb9	call   0x280024 <__assert_fail@plt>
0x283fbe	cmp    ecx,0x1
0x283fc1	jne    0x28400f <pthread_mutex_lock+255>
0x283fc3	mov    edx,DWORD PTR [ebp-0x10]
0x283fc6	cmp    edx,DWORD PTR [esi+0x8]
0x283fc9	je     0x283ff1 <pthread_mutex_lock+225>
0x283fcb	and    edi,0x80
0x283fd1	lock cmpxchg DWORD PTR [esi],ecx
0x283fd5	jne    0x284140 <_L_lock_839>
0x283fdb	cmp    DWORD PTR [esi+0x8],0x0
0x283fdf	jne    0x284096 <pthread_mutex_lock+390>
0x283fe5	mov    DWORD PTR [esi+0x4],0x1
0x283fec	jmp    0x283f68 <pthread_mutex_lock+88>
0x283ff1	mov    edx,DWORD PTR [esi+0x4]
0x283ff4	mov    eax,0xb
0x283ff9	cmp    edx,0xffffffff
0x283ffc	je     0x283f74 <pthread_mutex_lock+100>
0x284002	add    edx,0x1
0x284005	xor    al,al
0x284007	mov    DWORD PTR [esi+0x4],edx
0x28400a	jmp    0x283f74 <pthread_mutex_lock+100>
0x28400f	cmp    ecx,0x3
0x284012	jne    0x2840cb <pthread_mutex_lock+443>
0x284018	cmp    DWORD PTR [ebx+0x21cc],0x0
0x28401f	je     0x283f4a <pthread_mutex_lock+58>
0x284025	mov    edx,0x1
0x28402a	lock cmpxchg DWORD PTR [esi],edx
0x28402e	test   eax,eax
0x284030	je     0x284075 <pthread_mutex_lock+357>
0x284032	mov    eax,DWORD PTR [esi+0x14]
0x284035	mov    cl,0x1
0x284037	lea    edx,[eax+eax*1+0xa]
0x28403b	mov    eax,0x64
0x284040	cmp    edx,0x64
0x284043	cmovg  edx,eax
0x284046	xor    edi,edi
0x284048	add    edi,0x1
0x28404b	lea    eax,[edi-0x1]
0x28404e	cmp    eax,edx
0x284050	jge    0x2840ad <pthread_mutex_lock+413>
0x284052	pause
0x284054	xor    eax,eax
0x284056	lock cmpxchg DWORD PTR [esi],ecx
0x28405a	test   eax,eax
0x28405c	jne    0x284048 <pthread_mutex_lock+312>
0x28405e	mov    edx,edi
0x284060	mov    ecx,0x8
0x284065	sub    edx,DWORD PTR [esi+0x14]
0x284068	mov    eax,edx
0x28406a	sar    edx,0x1f
0x28406d	idiv   ecx
0x28406f	add    eax,DWORD PTR [esi+0x14]
0x284072	mov    DWORD PTR [esi+0x14],eax
0x284075	cmp    DWORD PTR [esi+0x8],0x0
0x284079	je     0x283f68 <pthread_mutex_lock+88>
0x28407f	lea    eax,[ebx-0x5586]
0x284085	mov    DWORD PTR [esp+0xc],eax
0x284089	mov    DWORD PTR [esp+0x8],0x71
0x284091	jmp    0x283fa6 <pthread_mutex_lock+150>
0x284096	lea    eax,[ebx-0x5586]
0x28409c	mov    DWORD PTR [esp+0xc],eax
0x2840a0	mov    DWORD PTR [esp+0x8],0x54
0x2840a8	jmp    0x283fa6 <pthread_mutex_lock+150>
0x2840ad	mov    eax,DWORD PTR [esi+0xc]
0x2840b0	mov    ecx,0x1
0x2840b5	and    eax,0x80
0x2840ba	mov    DWORD PTR [ebp-0x14],eax
0x2840bd	xor    eax,eax
0x2840bf	lock cmpxchg DWORD PTR [esi],ecx
0x2840c3	jne    0x28414e <_L_lock_979>
0x2840c9	jmp    0x28405e <pthread_mutex_lock+334>
0x2840cb	cmp    ecx,0x2
0x2840ce	jne    0x2840e6 <pthread_mutex_lock+470>
0x2840d0	mov    edx,DWORD PTR [ebp-0x10]
0x2840d3	mov    eax,0x23
0x2840d8	cmp    edx,DWORD PTR [esi+0x8]
0x2840db	jne    0x283f4a <pthread_mutex_lock+58>
0x2840e1	jmp    0x283f74 <pthread_mutex_lock+100>
0x2840e6	lea    eax,[ebx-0x5586]
0x2840ec	mov    DWORD PTR [esp+0xc],eax
0x2840f0	lea    eax,[ebx-0x4e6a]
0x2840f6	mov    DWORD PTR [esp+0x4],eax
0x2840fa	lea    eax,[ebx-0x54d0]
0x284100	mov    DWORD PTR [esp+0x8],0x75
0x284108	mov    DWORD PTR [esp],eax
0x28410b	call   0x280024 <__assert_fail@plt>
