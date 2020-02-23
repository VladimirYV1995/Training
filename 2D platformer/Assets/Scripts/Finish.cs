using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Finish : MonoBehaviour
{
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.GetComponent<Player>())
        {
            int coins = GameObject.FindObjectsOfType<Coin>().Length;
            if (coins == 0)
            {
                Debug.Log("Игра окончена");
            }
            else
            {
                Debug.Log("Не все монеты собраны");
            }
        }
    }
}
