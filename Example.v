Theorem plus_ass:
  forall x y z : nat,
  (x + y) + z = x + (y + z).

Proof.
  intros x y z.
  induction x.
    do 2 rewrite plus_O_n.
    reflexivity.

    do 3 rewrite plus_Sn_m.
    apply eq_S.
    rewrite IHx.
    reflexivity.
Qed.
