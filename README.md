# Graphics_Final-project using OpenGL

Christmas_the Nutcracker Suite


## 세부 구현
### 1. 모델링
1) 사슴 8마리
2) 선물상자 모음 5개
3) 토끼
4) 자동차
5) 병정 3명
6) Teapot
7) 평면 VBOPlane 4개로 직육면체 공간으로 우주 표현 8) 평면 하나는 바닥 역할

### 2. 애니메이션
[1번 키보드]
1) 선물상자 제자리에서 Y축 회전
2) 주전자 회전(Z축 방향)
[2번 키보드]
1) 토끼, 자동차
제자리에서 Y축 회전
원점 중심으로 translate, Y축 회전 2) 병정 3명
원점 중심으로 Y축 회전, 제자리에서 Z축 회전 [3번 키보드]
1) 주전자 회전(XY축 방향)
2) 사슴 8마리 0,0 중심으로 Y축 회전, translate

### 3. 렌더링
1) 퐁쉐이딩 (사슴, 선물상자, 토끼, 자동차, 병정)
2) 텍스처매핑 (평면 5개, 주전자)

### 4. 라이트
1) Ambient, diffuse, specular 조명
2) Ambient와 diffuse만 사용해서 부드러운 느낌의 조명

### 5. 파티클
1) 랜덤하게 떨어지는 눈 파티클 
2) 밑에서 올라오는 눈송이 파티클

### 6. 카메라
1) 마우스 오른쪽 버튼 - 360도 회전
2) 마우스 왼쪽 버튼 - 화면 옆으로 밀기
3) 마우스 가운데 버튼 누르고 끌어 당기면 줌아웃 4) 마우스 가운데 버튼 누르고 밀어 올리면 줌인
