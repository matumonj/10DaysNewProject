#include "OBBCollision.h"

// OBB v.s. OBB
using namespace DirectX;

bool OBBCollision::ColOBBs(OBB& obb1, OBB& obb2)
{
    // 各方向ベクトルの確保
    // （N***:標準化方向ベクトル）
    XMVECTOR NAe1 = obb1.GetDirect(0), Ae1 = { NAe1.m128_f32[0] * obb1.GetLen_W(0),NAe1.m128_f32[1] * obb1.GetLen_W(0),NAe1.m128_f32[2] * obb1.GetLen_W(0) };
    XMVECTOR NAe2 = obb1.GetDirect(1), Ae2 = { NAe2.m128_f32[0] * obb1.GetLen_W(1), NAe2.m128_f32[1] * obb1.GetLen_W(1), NAe2.m128_f32[2] * obb1.GetLen_W(1) };
    XMVECTOR NAe3 = obb1.GetDirect(2), Ae3 = { NAe3.m128_f32[0] * obb1.GetLen_W(2), NAe3.m128_f32[1] * obb1.GetLen_W(2), NAe3.m128_f32[2] * obb1.GetLen_W(2) };
    XMVECTOR NBe1 = obb2.GetDirect(0), Be1 = { NBe1.m128_f32[0] * obb2.GetLen_W(0),NBe1.m128_f32[1] * obb2.GetLen_W(0),NBe1.m128_f32[2] * obb2.GetLen_W(0) };
    XMVECTOR NBe2 = obb2.GetDirect(1), Be2 = { NBe2.m128_f32[0] * obb2.GetLen_W(1),NBe2.m128_f32[1] * obb2.GetLen_W(1),NBe2.m128_f32[2] * obb2.GetLen_W(1) };
    XMVECTOR NBe3 = obb2.GetDirect(2), Be3 = { NBe3.m128_f32[0] * obb2.GetLen_W(2),NBe3.m128_f32[1] * obb2.GetLen_W(2),NBe3.m128_f32[2] * obb2.GetLen_W(2) };
    XMVECTOR Interval = obb1.GetPos_W() - obb2.GetPos_W();
    
    // 分離軸 : Ae1
    double rA =sqrt((Ae1.m128_f32[0] * Ae1.m128_f32[0]) + (Ae1.m128_f32[1] * Ae1.m128_f32[1]) + (Ae1.m128_f32[2] * Ae1.m128_f32[2]));
    double rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    //XMVECTOR L = XMVector3Dot(Interval,NAe1);
    double fL = fabs((Interval.m128_f32[0] * NAe1.m128_f32[0]) + (Interval.m128_f32[1] * NAe1.m128_f32[1]) + (Interval.m128_f32[2] * NAe1.m128_f32[2]));
    if (fL > rA + rB) {
        return false;
    }
     // 分離軸 : Ae2
    rA = sqrt((Ae2.m128_f32[0] * Ae2.m128_f32[0]) + (Ae2.m128_f32[1] * Ae2.m128_f32[1]) + (Ae2.m128_f32[2] * Ae2.m128_f32[2]));
    rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    //L = XMVector3Dot(Interval, NAe2);
    fL = fabs((Interval.m128_f32[0] * NAe2.m128_f32[0]) + (Interval.m128_f32[1] * NAe2.m128_f32[1]) + (Interval.m128_f32[2] * NAe2.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }
    rA = sqrt((Ae3.m128_f32[0] * Ae3.m128_f32[0]) + (Ae3.m128_f32[1] * Ae3.m128_f32[1]) + (Ae3.m128_f32[2] * Ae3.m128_f32[2]));
    rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    //L = XMVector3Dot(Interval, NAe3);
    fL = fabs((Interval.m128_f32[0] * NAe3.m128_f32[0]) + (Interval.m128_f32[1] * NAe3.m128_f32[1]) + (Interval.m128_f32[2] * NAe3.m128_f32[2]));

    // 分離軸 : Ae3
    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : Be1
    rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = sqrt((Be1.m128_f32[0] * Be1.m128_f32[0]) + (Be1.m128_f32[1] * Be1.m128_f32[1]) + (Be1.m128_f32[2] * Be1.m128_f32[2]));
    //L = XMVector3Dot(Interval, NBe1);
    fL = fabs((Interval.m128_f32[0] * NBe1.m128_f32[0]) + (Interval.m128_f32[1] * NBe1.m128_f32[1]) + (Interval.m128_f32[2] * NBe1.m128_f32[2]));
    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : Be2
    rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = sqrt((Be2.m128_f32[0] * Be2.m128_f32[0]) + (Be2.m128_f32[1] * Be2.m128_f32[1]) + (Be2.m128_f32[2] * Be2.m128_f32[2]));
    //L = XMVector3Dot(Interval, NBe2);
    fL = fabs((Interval.m128_f32[0] * NBe2.m128_f32[0]) + (Interval.m128_f32[1] * NBe2.m128_f32[1]) + (Interval.m128_f32[2] * NBe2.m128_f32[2]));
    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : Be3
     rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
     rB = sqrt((Be3.m128_f32[0] * Be3.m128_f32[0]) + (Be3.m128_f32[1] * Be3.m128_f32[1]) + (Be3.m128_f32[2] * Be3.m128_f32[2]));
     //L = XMVector3Dot(Interval, NBe3);
     fL = fabs((Interval.m128_f32[0] * NBe3.m128_f32[0]) + (Interval.m128_f32[1] * NBe3.m128_f32[1]) + (Interval.m128_f32[2] * NBe3.m128_f32[2]));
     if (fL > rA + rB) {
         return false;
     }
    // 分離軸 : C11
    XMVECTOR Cross;
    Cross=XMVector3Cross(NAe1,NBe1);
    rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C12
    Cross=XMVector3Cross(NAe1, NBe2);
    rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C13
    Cross = XMVector3Cross(NAe1, NBe3);
    rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C21
    Cross = XMVector3Cross(NAe2, NBe1);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C22
    Cross = XMVector3Cross(NAe2, NBe2);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));
    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C23
    Cross = XMVector3Cross(NAe2, NBe3);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C31
    Cross = XMVector3Cross(NAe3, NBe1);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C32
    Cross = XMVector3Cross(NAe3, NBe2);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }
    // 分離軸 : C33
    Cross = XMVector3Cross(NAe3, NBe3);
  
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    //L = XMVector3Dot(Interval, Cross);
    fL = fabs((Interval.m128_f32[0] * Cross.m128_f32[0]) + (Interval.m128_f32[1] * Cross.m128_f32[1]) + (Interval.m128_f32[2] * Cross.m128_f32[2]));

    if (fL > rA + rB) {
        return false;
    }

    // 分離平面が存在しないので「衝突している」
    return true;
}


// 分離軸に投影された軸成分から投影線分長を算出
double OBBCollision::LenSegOnSeparateAxis(XMVECTOR* Sep, XMVECTOR* e1, XMVECTOR* e2, XMVECTOR* e3)
{
    // 3つの内積の絶対値の和で投影線分長を計算
    // 分離軸Sepは標準化されていること
    //XMVECTOR r1 = XMVector3Dot(Sep, e1);
    double fr1=fabs((Sep->m128_f32[0]*e1->m128_f32[0])+ (Sep->m128_f32[1] * e1->m128_f32[1])+ (Sep->m128_f32[2] * e1->m128_f32[2]));
   // FLOAT r2 = fabs(D3DXVec3Dot(Sep, e2));
    double fr2 = fabs((Sep->m128_f32[0] * e2->m128_f32[0]) + (Sep->m128_f32[1] * e2->m128_f32[1]) + (Sep->m128_f32[2] * e2->m128_f32[2]));
   // FLOAT r3 = e3 ? (fabs(D3DXVec3Dot(Sep, e3))) : 0;
    double fr3 = e3 ? (fabs((Sep->m128_f32[0] * e3->m128_f32[0]) + (Sep->m128_f32[1] * e3->m128_f32[1]) + (Sep->m128_f32[2] * e3->m128_f32[2]))) : 0;
    return fr1 + fr2 + fr3;
}